#include <thread>
#include <vector>
#include <queue>
#include <future>
#include <functional> // Для std::function и std::bind
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <chrono>

class ThreadPool {
private:
    std::vector<std::thread> workers;        // Вектор для хранения рабочих потоков
    std::queue<std::function<void()>> tasks; // Очередь задач (задачи - функции без аргументов)
    std::mutex queue_mutex;
    std::condition_variable condition; // Условная переменная для пробуждения потоков
    bool stop = false;                 // Флаг остановки пула (инициализирован false)
    
public:
    ThreadPool(size_t num_threads) {
        for (size_t i = 0; i < num_threads; ++i) {
            workers.emplace_back([this] {
                while (true) { // бесконечный цикл
                    std::function<void()> task;
                    
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        // Ждем пока не будет задачи ИЛИ не придет команда остановки
                        this->condition.wait(lock, [this] {
                            return this->stop || !this->tasks.empty();
                        });
                        // Если остановка И очередь пуста - выходим из цикла
                        if (this->stop && this->tasks.empty())
                            return;
                            
                        task = std::move(this->tasks.front()); // Забираем задачу из очереди (перемещаем)
                        this->tasks.pop();  // Удаляем задачу из очереди
                    } // Конец блока - lock автоматически освобождается
                    
                    task(); // делаем задачу
                }
            });
        }
    }
    
    template<class F, class... Args>                           // Шаблонный метод с переменным числом аргументов
    auto submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
    // auto определяет тип возвращаемого значения, decltype определяет тип результата функции f
    
    using return_type = decltype(f(args...));               // Создаем псевдоним для типа возвращаемого значения
    
    // Создаем packaged_task - обертку над функцией, которая может вернуть future
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        // std::bind привязывает аргументы к функции
        // std::forward передает аргументы с сохранением категории значения (lvalue/rvalue)
    );
    
    // Получаем future для получения результата
    std::future<return_type> result = task->get_future();
    
    {                                                       // Начало блока синхронизации
        std::unique_lock<std::mutex> lock(queue_mutex);     // Захватываем мьютекс
        
        if (stop) {                                         // Проверяем, не остановлен ли пул
            throw std::runtime_error("submit called on stopped ThreadPool");}
        
        // Добавляем задачу в очередь
        // Задача - лямбда-функция, которая вызывает packaged_task
        tasks.emplace([task]() { (*task)(); }); 
    }                                                    
    
    condition.notify_one(); // Пробуждаем один ожидающий поток
    return result;  // Возвращаем future
    }
    
    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        
        condition.notify_all();
        
        for (std::thread &worker : workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
    }
};
// Функция для демонстрации - вычисление факториала
unsigned long long factorial(int n) {
    if (n < 0) return 0;
    if (n == 0 || n == 1) return 1;
    
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}

int main() {

    ThreadPool pool(4); // Создаем пул из 4 потоков
    std::vector<std::future<unsigned long long>> results; // Вектор для хранения future
    
    std::cout << "Запускаем вычисление факториалов через пул потоков...\n";
    
    // Добавляем задачи в пул
    for (int i = 1; i <= 10; ++i) {
        results.emplace_back(
            pool.submit(factorial, i)
        );
    }
    
    // Получаем результаты
    for (size_t i = 0; i < results.size(); ++i) {
        int n = i + 1;
        unsigned long long result = results[i].get();
        std::cout << "Факториал " << n << " = " << result << std::endl;
    }
    
    // Демонстрация асинхронных вычислений
    std::cout << "\nДемонстрация параллельных вычислений:\n";
    
    auto start_time = std::chrono::high_resolution_clock::now();
    
    std::vector<std::future<unsigned long long>> parallel_results;
    for (int i = 15; i <= 20; ++i) {
        parallel_results.emplace_back(pool.submit(factorial, i));
    }
    
    for (size_t i = 0; i < parallel_results.size(); ++i) {
        int n = i + 15;
        std::cout << "Факториал " << n << " = " << parallel_results[i].get() << std::endl;
    }
    
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    std::cout << "\nВсе вычисления завершены за " << duration.count() << " мс\n";
    
    return 0;
}
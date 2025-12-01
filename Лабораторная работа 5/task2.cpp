#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <random>
// lock_guard - только для простой блокировки
// unique_lock - может временно отпускать блокировку (нужно для wait())

template<typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable cond;
    bool shutdown_flag = false;
    
public:
    void push(T value) {
        // TODO: Реализовать потокобезопасное добавление
        std::lock_guard<std::mutex> guard(mutex);
        queue.push(value);
        std::cout << "элемент " << value <<  " добавлен в очередь" << std::endl;
        cond.notify_one(); // уведомляем ожидающий поток
    }
    
    bool pop(T& value) { // по ссылке чтобы обновить в консьюмере
        // TODO: Реализовать потокобезопасное извлечение
        // Возвращать false если очередь закрыта и пуста

        // ждём пока не появится элемент или не закроют очередь
        std::unique_lock<std::mutex> uni_guard(mutex);  
        cond.wait(uni_guard, [this]() { 
            return !queue.empty() || shutdown_flag; 
        });

        if (queue.empty() && shutdown_flag) {
            std::cout << "очередь закрыта и пуста " << std::endl;
            return false;
        } 
        
        value = queue.front();
        queue.pop();
        std::cout << "Элемент " << value << " извлечен из очереди" << std::endl;
        return true;
    }
    
    void shutdown() {
        std::lock_guard<std::mutex> guard(mutex);
        shutdown_flag = true;
        cond.notify_all(); // УВЕДОМЛЯЕМ ВСЕ ожидающие потоки
    }
    
    bool is_shutdown() const {
        return shutdown_flag;
    }
};

void producer(ThreadSafeQueue<int>& queue, int count) {
    // TODO: Генерировать числа и помещать в очередь
    for (int i=0; i<count; ++i) {
        int rand_count = rand() % 100 + 1; // случайные числа 1-100 (%100 остаток от деления на 100)
        queue.push(rand_count);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // имитация обработки
    }
    std::cout << "\nПроизводитель завершил работу" << std::endl;
}

void consumer(ThreadSafeQueue<int>& queue, int id) {
    // TODO: Извлекать и обрабатывать числа из очереди
    int value; // пустая переменная, потом заполнится в поп
    while (queue.pop(value)) { // пока тру
        std::cout << "Потребитель " << id << " обработал: " << value 
                  << " (результат: " << value * 2 << ")" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // имитация обработки
    }
    std::cout << "\nПотребитель " << id << " завершил работу" << std::endl;
}

int main() {

    ThreadSafeQueue<int> queue1; // тип int

    // Реализовать один поток-производитель, который генерирует числа
    std::thread th0([&queue1](){
        producer(queue1, 10);
    });
    // Реализовать три потока-потребителя, которые обрабатывают числа
    std::thread th1([&queue1](){
        consumer(queue1, 1);
    });
    std::thread th2([&queue1](){
        consumer(queue1, 2);
    });
    std::thread th3([&queue1](){
        consumer(queue1, 3);
    });

    th0.join();
    // закрыть очередь после завершения производителя
    std::cout << "Закрываем очередь..." << std::endl;
    queue1.shutdown();

    th1.join();
    th2.join();
    th3.join();

    std::cout << "Все потоки завершены!" << std::endl;
    return 0;

}
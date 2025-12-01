#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>

class VectorSumCalculator {
private:
    std::vector<int> data; // умный контейнер, не надо очищать память
    std::mutex sum_mutex;
    std::mutex cout_mutex;
    
public:
    VectorSumCalculator(size_t size) {
        // TODO: Заполнить вектор случайными числами
        data.resize(size); // выделили память, а то сначала был пустой
        for (size_t i = 0; i < size; ++i) {
        data[i] = rand() % 100 + 1; // ранд до 32767, случайные числа 1-100 (%100 остаток от деления на 100)
        }
    }
    
    // Однопоточное вычисление суммы
    long long calculateSingleThreaded() {
        // TODO: Реализовать однопоточное вычисление

        std::cout << "\nStart Single Threaded " << std::endl;
        std::cout << "ID потока: " << std::this_thread::get_id() << std::endl;
        long long sum = 0;
        for (int value : data) {
            sum += value;
        }
        return sum;
    }
    
    // Многопоточное вычисление суммы
    long long calculateMultiThreaded(int num_threads) {
        // TODO: Реализовать многопоточное вычисление
        // Разделить вектор на части, создать потоки,
        // использовать мьютекс для защиты общей суммы
        
        std::cout << "\nStart Multi Threaded " << std::endl;
        int part_size = data.size() / num_threads; // размер куска для каждого потока
        long long total_sum = 0;
        
        // вектор для хранения потоков 
        std::vector<std::thread> threads;
        for (int i = 0; i < num_threads; ++i) { // создаем куски, каждый кусок в свой поток, в потоке считаем, потом суммируем
            int start = part_size * i;
            int end = part_size * (i+1);

            // push_back - создает + копирует, а emplace_back сразу создает объект ВНУТРИ вектора
            threads.emplace_back([this,i,start,end,&total_sum]() { // this чтобы видеть поля класса, по ссылке чтобы менялось значение
                // вывод в консоль
                cout_mutex.lock();
                std::cout << "i = " << i << ", ID потока: " << std::this_thread::get_id() << std::endl;
                cout_mutex.unlock();

                long long part_sum = 0;
                for (int n = start; n < end; ++n) {
                    part_sum += data[n];
                }

                // вывод в консоль
                cout_mutex.lock();
                std::cout << "part_sum[" << i << "] = " << part_sum << std::endl;
                cout_mutex.unlock();

                sum_mutex.lock();
                total_sum += part_sum;
                sum_mutex.unlock();
            });
        }
        // ждем завершения всех потоков после их запуска
        for (auto& thread : threads) {
            thread.join();
        }
        
        return total_sum;
    }
};

int main() {
    // TODO: Создать объект, выполнить оба расчета,
    // замерить время и сравнить результаты
    const size_t data_size = 10000000; 
    const int num_threads = 4;
    
    VectorSumCalculator calculator(data_size);
    std::cout << "вектор заполнен числами!" << std::endl;

    auto start_time = std::chrono::high_resolution_clock::now();
    long long single_sum = calculator.calculateSingleThreaded();
    auto end_time = std::chrono::high_resolution_clock::now();
    auto single_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

    start_time = std::chrono::high_resolution_clock::now();
    long long multi_sum = calculator.calculateMultiThreaded(num_threads);
    end_time = std::chrono::high_resolution_clock::now();
    auto multi_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    std::cout << "\nРезультаты:" << std::endl;
    std::cout << "Однопоточная сумма: " << single_sum << std::endl;
    std::cout << "Многопоточная сумма: " << multi_sum << std::endl;
    if (single_sum == multi_sum) {
        std::cout << "Суммы совпадают!" << std::endl;
    } else {
        std::cout << "Ошибка: суммы не совпадают!" << std::endl;
    }
    std::cout << "Время однопоточного вычисления: " << single_duration.count() << " мс" << std::endl;
    std::cout << "Время многопоточного вычисления: " << multi_duration.count() << " мс" << std::endl;
}
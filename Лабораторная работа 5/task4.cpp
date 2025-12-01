#include <future>
#include <random>
#include <vector>
#include <stdexcept>
#include <iostream>

class PiCalculator {
private:
    std::mutex cout_mutex;

public:
    
    // Вычисление π с использованием заданного количества точек
    double calculatePiPortion(int total_points) {
        if (total_points <= 0) {
            throw std::invalid_argument("Количество точек должно быть положительным");
        }
        
        int points_inside_circle = 0;

        for (int i = 0; i < total_points; ++i) {
            // Генерируем случайную точку в квадрате [-1,1]x[-1,1]
            // Делим случайное число на максимально возможное, получаем число от 0.0 до 1.0
            // Умножаем на 2, чтобы расширить диапазон, получаем числа от 0.0 до 2.0
            // Вычитаем 1, чтобы сместить диапазон, получаем числа от -1.0 до 1.0
            double x = (2.0 * rand() / RAND_MAX) - 1.0;  // RAND_MAX = 32767 // от -1.0 до 1.0
            double y = (2.0 * rand() / RAND_MAX) - 1.0;  // RAND_MAX = 32767 // от -1.0 до 1.0
            
            // Проверяем, попадает ли точка в единичную окружность (ур окр x² + y² = R²)
            if (x * x + y * y <= 1.0) {
                points_inside_circle++;
            }
        }
        
        // Вычисляем π: (4 * точки_в_окружности) / общее_количество_точек
        // S_квадрата = 2 × 2 = 4
        // S_окружности = π × r² = π × 1² = π
        // S_окружности / S_квадрата = π / 4
        double rez = 4.0 * static_cast<double>(points_inside_circle) / static_cast<double>(total_points);
        cout_mutex.lock();
        std::cout << "ID потока: " << std::this_thread::get_id() << "\nrez = " << rez << "\npoints_per_task = " << total_points << std::endl << std::endl;
        cout_mutex.unlock();
        
        return rez;
    }

    // Параллельное вычисление π
    double calculatePiParallel(int total_points, int num_tasks) {
        if (total_points <= 0) {
            throw std::invalid_argument("Общее количество точек должно быть положительным");
        }
        if (num_tasks <= 0) {
            throw std::invalid_argument("Количество задач должно быть положительным");
        }
        
        std::vector<std::future<double>> futures;
        int points_per_task = total_points / num_tasks;
        int remaining_points = total_points % num_tasks; // Остаточные точки
        std::cout << "remaining_points: " << remaining_points << std::endl;

        // Создаем асинхронные задачи
        for (int i = 0; i < num_tasks; ++i) {
            // Распределяем остаточные точки по первым задачам
            int task_points = points_per_task + (i < remaining_points ? 1 : 0);
            
            if (task_points > 0) {
                // Создаем асинхронную задачу с политикой std::launch::async
                futures.push_back(
                    std::async(std::launch::async, &PiCalculator::calculatePiPortion, this, task_points)
                );
            }
        }

        // Собираем и усредняем результаты
        double sum = 0.0;
        int completed_tasks = 0;
        
        for (auto& future : futures) {
            try {
                // Получаем результат (может бросить исключение)
                double result = future.get();
                sum += result;
                completed_tasks++;
            }
            catch (const std::exception& e) {
                std::cerr << "Ошибка в асинхронной задаче: " << e.what() << std::endl;
                // Продолжаем обработку остальных задач
            }
        }
        
        if (completed_tasks == 0) {
            throw std::runtime_error("Все асинхронные задачи завершились с ошибкой");
        }
        
        // Усредняем результаты всех успешных задач
        return sum / completed_tasks;
    }
};

int main() {

    PiCalculator calculator;
    
    int total_points = 1000002;
    int num_tasks = 4;
    
    try {
        double pi = calculator.calculatePiParallel(total_points, num_tasks);
        
        std::cout << "Вычисленное значение π: " << pi << std::endl;
        std::cout << "Точное значение π: 3.1415926535" << std::endl;
        std::cout << "Погрешность: " << std::abs(pi - 3.1415926535) << std::endl;
        std::cout << "Количество точек: " << total_points << std::endl;
        std::cout << "Количество задач: " << num_tasks << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}


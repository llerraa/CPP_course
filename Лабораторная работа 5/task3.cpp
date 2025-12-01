#include <vector>
#include <thread>
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>

class ImageProcessor {
private:
    std::vector<std::vector<int>> image;
    int width, height;
    
public:
    ImageProcessor(int w, int h) : width(w), height(h) {
        // TODO: Инициализировать "изображение" случайными значениями
        // двумерный вектор размером height x width
        // image.resize(height, ...) количество строк = height
        // std::vector<int>(width) каждая строка это вектор из width элементов
        // во временном все элементы автоматически инициализируются 0
        image.resize(height, std::vector<int>(width));
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                image[y][x] = rand() % 256;  // числа от 0 до 255
        }   }
    }

    // Фильтр размытия (усреднение 3x3)
    int blurPixel(int x, int y) {
        int sum = 0;
        int count = 0;
        
        // окрестность 3x3 вокруг пикселя 
        for (int dy = -1; dy <= 1; ++dy) { // dy: -1, 0, +1 (по вертикали)
            for (int dx = -1; dx <= 1; ++dx) { // dx: -1, 0, +1 (по горизонтали)
                int nx = x + dx; // координата x соседа
                int ny = y + dy; // координата y соседа

                // проверяем, не вышли ли за границы изображения
                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    sum += image[ny][nx]; // добавили яркость
                    count++; // увеличили счетчик
                }
            }
        }
        
        return (count > 0) ? sum / count : image[y][x]; // если нашли хоть одного соседа, то возвращаем среднее, если нет, то исходное
    } 

    // Однопоточное применение фильтра
    void applyFilterSingleThread() {
        // TODO: Реализовать последовательное применение фильтра
        std::vector<std::vector<int>> result(height, std::vector<int>(width));
        
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                result[y][x] = blurPixel(x, y);
            }
        }
        
        image = std::move(result); // удобная штука для того, чтобы не копировать (долго), а переносить (result становится пустым, image получает его данные)
    }
    
    // Многопоточное применение фильтра
    void applyFilterMultiThread(int num_threads) {
        // TODO: Разделить изображение на части,
        // создать потоки для обработки каждой части

        std::vector<std::vector<int>> result(height, std::vector<int>(width));
        std::vector<std::thread> threads; // вектор потоков
        
        int rows_per_thread = height / num_threads;
        
        for (int i = 0; i < num_threads; ++i) {
            int start_row = i * rows_per_thread;
            int end_row = (i == num_threads - 1) ? height : (i + 1) * rows_per_thread;
            
            threads.emplace_back([this, start_row, end_row, &result]() {
                for (int y = start_row; y < end_row; ++y) {
                    for (int x = 0; x < width; ++x) {
                        result[y][x] = this->blurPixel(x, y);
                    }
                }
            });
        }
        
        for (auto& thread : threads) {
            thread.join();
        }
        
        image = std::move(result);
    }

    // ВЫВОД ИЗОБРАЖЕНИЯ (первые 10x10 пикселей)
    void printImage() {
        std::cout << "Первые 10x10 пикселей:" << std::endl;
        for (int y = 0; y < std::min(10, height); ++y) {
            for (int x = 0; x < std::min(10, width); ++x) {
                std::cout << image[y][x] << "\t";
            }
            std::cout << std::endl;
        }
    }
    
};

int main() {
    const int width = 1000;
    const int height = 1000;
    const int num_threads = 4;
    
    ImageProcessor processor(width, height);

    std::cout << "ДО обработки" << std::endl;
    processor.printImage();

    // Однопоточная обработка
    auto start_time = std::chrono::high_resolution_clock::now();
    processor.applyFilterSingleThread();
    auto end_time = std::chrono::high_resolution_clock::now();
    auto single_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    std::cout << "Время однопоточной обработки: " << single_duration.count() << " мс" << std::endl;
    
    std::cout << "ПОСЛЕ обработки" << std::endl;
    processor.printImage();

    // Создаем новое изображение для многопоточной обработки
    ImageProcessor processor2(width, height);
    
    // Многопоточная обработка
    start_time = std::chrono::high_resolution_clock::now();
    processor2.applyFilterMultiThread(num_threads);
    end_time = std::chrono::high_resolution_clock::now();
    auto multi_duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    
    std::cout << "Время многопоточной обработки: " << multi_duration.count() << " мс" << std::endl;
        
    return 0;
}
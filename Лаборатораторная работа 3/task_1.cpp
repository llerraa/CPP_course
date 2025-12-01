// Реализовать класс с инкапсуляцией данных

#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    // TODO: Добавить приватные поля: имя, возраст, средний балл, массив оценок (5 элементов)
    string name;
    int age;
    double sr_ball;
    int grades[5];

public:
    // TODO: Создать конструктор с параметрами
    Student(string n, int a) : name(n), age(a) {
        sr_ball = 0; // по умолчанию
        for (int i = 0; i<5; ++i){ // по умолчанию
            grades[i] = 0;
        }        
    }

    // TODO: Реализовать геттеры и сеттеры с валидацией
    string GetName() const{
        return name;
    }
    
    int GetAge() const{
        return age;
    }
    
    double GetSBall() const{
        return sr_ball;
    }
    
    const int* GetGrades() const{
        return grades;
    }

    void SetName(string new_name){
        if (new_name.length() < 3) {
            cout << "имя не может быть из 1-2 буквы, введите реальное имя" << endl;
        } else {
        name = new_name;
        cout << "имя успешно установлено!" << endl;
        }
    }
    
    void SetAge(int new_age){
        if (new_age < 17) {
            cout << "ребенок слишком мал, это не студент, введите возраст 17+" << endl;
        } else {
        age = new_age;
        cout << "возраст успешно установлен!" << endl;
        }
    }

    void setGrade(int number, int mark){
        if (number < 0 || number >= 5) {
            cout << "неверный индекс оценки (должен быть от 0 до 4)" << endl;
        } else if (mark < 2 || mark > 5) {
            cout << "оценка должна быть от 2 до 5" << endl;
        } else {
        grades[number] = mark;
        cout << number+1 << "-ая оценка успешно вбита!" << endl;
        }
    }

    // TODO: Метод для расчета среднего балла
    double count_sr_ball(){
        double summa = 0;
        for (int i = 0; i < 5; ++i) { 
            summa += grades[i]; 
        }
        sr_ball = summa / 5; // возможно надо через сеттер?
        return sr_ball;
    }
    
    // TODO: Метод для вывода информации о студенте
    void displayInfo(){
        cout << "студент: " << name << ", \n возраст: " << age << ", \n средний балл: " << count_sr_ball() << ", \n оценки: " << endl;
        for (int i = 0; i < 5; ++i) { 
            cout << grades[i] << endl; 
        }
    }
    
    // TODO: Метод для проверки стипендии (средний балл >= 4.5)
    bool hasScholarship() {
        if (count_sr_ball() >= 4.5) {
            return true;
        }
        else {
            return false;
        }
    }
};

int main() {
    // Тестирование класса Student
    Student student("Иван Иванов", 20);
        
    // Установка оценок
    student.setGrade(0, 5);
    student.setGrade(1, 4);
    student.setGrade(2, 5);
    student.setGrade(3, 3);
    student.setGrade(4, 4);
    
    student.displayInfo();
    
    if (student.hasScholarship()) {
        cout << "Студент получает стипендию" << endl;
    } else {
        cout << "Стипендия не назначена" << endl;
    }
    
    // еще сеттеры надо бы проверить на работоспособность
    cout << "\n —————————————–––––––– \n" << endl;
    Student student_test("Ноу Нейм Пупкин", 20);

    student_test.SetAge(16); // выведет ошибку
    student_test.SetName("А"); // выведет ошибку

    const int* grades_until_set = student_test.GetGrades(); // покажет нули
    double sr_ball_until_set = student_test.GetSBall(); // покажет ноль
    cout << "средний балл до установки (автоматически): " << sr_ball_until_set << endl;
    cout << "оценки до установки (автоматически): " << endl;
    for (int i = 0; i < 5; ++i) {
        cout << grades_until_set[i] << endl;
    }

    student_test.setGrade (0, 5);
    student_test.setGrade (1, 5);
    student_test.setGrade (7, 5); // выведет ошибку
    student_test.setGrade (2, 7); // выведет ошибку
    student_test.setGrade (2, 4);
    student_test.setGrade (3, 5);
    student_test.setGrade (4, 4);

    student_test.displayInfo(); // оставит Пупкина и 20
    if (student_test.hasScholarship()) {
        cout << "Студент получает стипендию" << endl;
    } else {
        cout << "Стипендия не назначена" << endl;
    }

    return 0;
}
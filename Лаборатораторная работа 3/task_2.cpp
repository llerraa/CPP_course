//  Создать иерархию классов с использованием наследования.

#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;
    string address;

public:
    Person(string n, int a, string addr) : name(n), age(a), address(addr) {}
    
    virtual void displayInfo() const {
        cout << "\nИмя: " << name << ", Возраст: " << age << ", Адрес: " << address << endl;
    }
    
    // геттер нужен для красивого отображения стипендии и надбавкив main
    string GetName() const{
        return name;
    }

    virtual ~Person() {}
};

class Student : public Person {
private:
    string studentId;
    double averageGrade;

public:
    // TODO: Создать конструктор
    Student(string n, int a, string addr, string i, double g) : Person(n, a, addr), studentId(i), averageGrade(g) {}
   
    // TODO: Переопределить displayInfo()
    void displayInfo() const override {
        cout << "\nИмя: " << name << ", Возраст: " << age << ", Адрес: " << address << ", Id: " << studentId << ", Средний балл: " << averageGrade << endl;
    }

    // TODO: Добавить методы для работы с оценками
    // сделала метод для проверки стипендии (средний балл >= 4.5)
    bool hasScholarship() {
        if (averageGrade >= 4.5) {
            return true;
        }
        else {
            return false;
        }
    }
};

class Professor : public Person {
private:
    string department;
    double salary;
    int yearsOfExperience;

public:
    // TODO: Создать конструктор
    Professor(string n, int a, string addr, string d, double s, int y) : Person(n, a, addr), department(d), salary(s), yearsOfExperience(y) {}
    
    // TODO: Переопределить displayInfo()
    void displayInfo() const override {
        cout << "\nИмя: " << name << ", Возраст: " << age << ", Адрес: " << address << ", Департамент: " << department << ", Зарплата: " << salary << ", Стаж: " << yearsOfExperience << endl;
    }

    // TODO: Добавить метод для расчета надбавки за стаж
    // сделала так что каждый год стажа даёт +1000 к базовой зп
    int nadbavka(){
        int baze_salary = 35000;
        int size_of_nadbavka = 0;
        int actual_salary = 35000;
        for (int i = 0; i < yearsOfExperience; ++i) {
            size_of_nadbavka +=1000;
        }
        actual_salary += size_of_nadbavka;
        return size_of_nadbavka;
    }
};

int main() {
    
    // Тестирование иерархии классов
    Student student("Петр Петров", 20, "ул. Студенческая, 15", "S12345", 4.3);
    Professor prof("Доктор Иванов", 45, "ул. Академическая, 10", "Компьютерные науки", 50000, 15);
    
    student.displayInfo();
    prof.displayInfo();

    if (student.hasScholarship()) {
        cout << "\nстудент " << student.GetName() << " получает стипендию" << endl;
    } else {
        cout << "\nстуденту " << student.GetName() << " стипендия не назначена" << endl;
    }
    
    cout << "\nразмер надбавки за стаж у " << prof.GetName() << ": " << prof.nadbavka() << " руб." << endl;

    return 0;
}
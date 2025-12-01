#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;

public:
    Person(string n, int a) : name(n), age(a) {}
    virtual void display() const {
        cout << "имя: " << name << ", возраст: " << age << endl;
    }
};

class Employee {
protected:
    string position;
    double salary;

public:
    Employee(string pos, double sal) : position(pos), salary(sal) {}
    virtual void work() const {
        cout << "выполняет работу как сотрудник" << endl;
    }
};

// класс Teacher, наследование от Person и Employee
class Teacher : public Person, public Employee {
private:
    string subject;
    int experienceYears;

public:
    // конструктор
    Teacher(string n, int a, string pos, double sal, string subj, int exp)
        : Person(n, a), Employee(pos, sal), subject(subj), experienceYears(exp) {}
    
    // переопределение методов
    void display() const override {
        Person::display();
        cout << "должность: " << position << endl;
        cout << "зарплата: " << salary << endl;
        cout << "предмет: " << subject << endl;
        cout << "опыт работы: " << experienceYears << " лет" << endl;
    }
    
    void work() const override {
        cout << name << " преподает предмет '" << subject << "'" << endl;
    }
    
    // специфичные методы для Teacher
    void gradeStudents() const {
        cout << name << " выставляет оценки по предмету '" << subject << "'" << endl;
    }
    
    void prepareLesson() const {
        cout << name << " готовится к уроку по предмету '" << subject << "'" << endl;
    }
    
    // геттеры
    string getSubject() const { return subject; }
    int getExperience() const { return experienceYears; }
};

class Researcher {
protected:
    string researchArea;
    int publicationsCount;

public:
    Researcher(string area, int publications) 
        : researchArea(area), publicationsCount(publications) {}
    
    void conductResearch() const {
        cout << "проводит исследования в области: " << researchArea << endl;
    }
    
    virtual void displayResearch() const {
        cout << "область исследований: " << researchArea 
             << ", публикаций: " << publicationsCount << endl;
    }
};

// класс Professor, наследующий от Teacher и Researcher
class Professor : public Teacher, public Researcher {
private:
    string academicDegree;

public:
    // конструктор
    Professor(string n, int a, string pos, double sal, string subj, int exp,
              string area, int publications, string degree)
        : Teacher(n, a, pos, sal, subj, exp), 
          Researcher(area, publications), 
          academicDegree(degree) {}
    
    // переопределение методов
    void display() const override {
        Person::display();  // Person из Teacher
        cout << "должность: " << position << endl;
        cout << "зарплата: " << salary << endl;
        cout << "предмет: " << getSubject() << endl;
        cout << "опыт работы: " << getExperience() << " лет" << endl;
        cout << "ученая степень: " << academicDegree << endl;
        displayResearch();
    }
    
    void work() const override {
        cout << name << " работает как профессор" << endl;
        teach();
        conductResearch();
    }
    
    // Специфичные методы для Professor
    void teach() const {
        cout << name << " читает лекции по предмету '" << getSubject() << "'" << endl;
    }
    
    void supervisePhD() const {
        cout << name << " руководит аспирантами в области '" << researchArea << "'" << endl;
    }
    
    void publishPaper() {
        publicationsCount++;
        cout << name << " опубликовал новую статью, всего публикаций: " << publicationsCount << endl;
    }
};

int main() {
    
    // объект Teacher
    Teacher teacher("Анна Иванова", 35, "Старший преподаватель", 50000, 
                   "Математика", 10);
    
    teacher.display();
    teacher.work();
    teacher.gradeStudents();
    teacher.prepareLesson();
    
    // объект Professor
    Professor professor("Петр Сидоров", 45, "Профессор", 80000,
                       "Физика", 20, "Квантовая механика", 15, "Доктор наук");
    
    professor.display();
    professor.work();
    professor.teach();
    professor.supervisePhD();
    professor.publishPaper();
    professor.conductResearch();
    
    // полиморфизм
    Person* personPtr = &teacher;
    Employee* employeePtr = &teacher;
    
    cout << "\nЧерез указатель на Person:" << endl;
    personPtr->display();
    
    cout << "\nЧерез указатель на Employee:" << endl;
    // employeePtr->work(); // не сработает, нужно преобразование
    
    // для профессора
    Person* personProf = &professor;
    Employee* employeeProf = &professor;
    Researcher* researcherProf = &professor;
    
    cout << "как Person:" << endl;
    personProf->display();
    
    cout << "\nкак Researcher:" << endl;
    researcherProf->conductResearch();
    researcherProf->displayResearch();
    
    // методы базовых классов
    professor.Teacher::work();  // вызов метода из Teacher
    professor.Researcher::conductResearch();  // вызов метода из Researcher
    
    return 0;
}
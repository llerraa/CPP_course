#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

// абстрактный базовый класс
class universitymember {
protected:
    string name;
    string id;
    string email;

public:
    universitymember(string n, string i, string e) : name(n), id(i), email(e) {}
    virtual ~universitymember() {}
    
    // чисто виртуальные методы
    virtual void displayinfo() const = 0;
    virtual void work() const = 0;
    virtual string getrole() const = 0;
    
    // геттеры
    string getname() const { return name; }
    string getid() const { return id; }
    string getemail() const { return email; }
};

class student : public universitymember {
private:
    string major;
    int year;
    double gpa;
    vector<string> courses;

public:
    student(string n, string i, string e, string m, int y) 
        : universitymember(n, i, e), major(m), year(y), gpa(0.0) {}
    
    void displayinfo() const {
        cout << "имя: " << name << endl;
        cout << "id: " << id << endl;
        cout << "email: " << email << endl;
        cout << "специальность: " << major << endl;
        cout << "курс: " << year << endl;
        cout << "gpa: " << gpa << endl;
        cout << "количество курсов: " << courses.size() << endl;
        if (!courses.empty()) {
            cout << "курсы: ";
            for (size_t i = 0; i < courses.size(); i++) {
                cout << courses[i];
                if (i < courses.size() - 1) cout << " ";
            }
            cout << endl;
        }
    }
    
    void work() const {
        cout << name << " учится на " << year << " курсе по специальности " << major << endl;
    }
    
    string getrole() const {
        return "студент";
    }
    
    void enrollcourse(const string& course) {
        if (find(courses.begin(), courses.end(), course) == courses.end()) {
            courses.push_back(course);
            cout << name << " записан на курс: " << course << endl;
        } else {
            cout << name << " уже записан на курс: " << course << endl;
        }
    }
    
    void dropcourse(const string& course) {
        vector<string>::iterator it = find(courses.begin(), courses.end(), course);
        if (it != courses.end()) {
            courses.erase(it);
            cout << name << " отчислен с курса: " << course << endl;
        } else {
            cout << name << " не записан на курс: " << course << endl;
        }
    }
    
    void calculategpa(double newgpa) {
        gpa = newgpa;
        cout << name << " обновлен gpa: " << gpa << endl;
    }
    
    string getmajor() const { return major; }
    int getyear() const { return year; }
    double getgpa() const { return gpa; }
    const vector<string>& getcourses() const { return courses; }
};

class professor : public universitymember {
private:
    string department;
    string office;
    double salary;
    vector<string> teachingcourses;

public:
    professor(string n, string i, string e, string d, string o, double s) 
        : universitymember(n, i, e), department(d), office(o), salary(s) {}
    
    void displayinfo() const {
        cout << "имя: " << name << endl;
        cout << "id: " << id << endl;
        cout << "email: " << email << endl;
        cout << "кафедра: " << department << endl;
        cout << "офис: " << office << endl;
        cout << "зарплата: " << salary << endl;
        cout << "количество преподаваемых курсов: " << teachingcourses.size() << endl;
        if (!teachingcourses.empty()) {
            cout << "курсы: ";
            for (size_t i = 0; i < teachingcourses.size(); i++) {
                cout << teachingcourses[i];
                if (i < teachingcourses.size() - 1) cout << " ";
            }
            cout << endl;
        }
    }
    
    void work() const {
        cout << name << " преподает на кафедре " << department << " в офисе " << office << endl;
    }
    
    string getrole() const {
        return "преподаватель";
    }
    
    void assigncourse(const string& course) {
        if (find(teachingcourses.begin(), teachingcourses.end(), course) == teachingcourses.end()) {
            teachingcourses.push_back(course);
            cout << name << " назначен на курс: " << course << endl;
        } else {
            cout << name << " уже преподает курс: " << course << endl;
        }
    }
    
    void removecourse(const string& course) {
        vector<string>::iterator it = find(teachingcourses.begin(), teachingcourses.end(), course);
        if (it != teachingcourses.end()) {
            teachingcourses.erase(it);
            cout << name << " снят с курса: " << course << endl;
        } else {
            cout << name << " не преподает курс: " << course << endl;
        }
    }
    
    void calculatesalary(double bonus = 0) {
        salary += bonus;
        cout << name << " новая зарплата: " << salary << " (бонус: " << bonus << ")" << endl;
    }
    
    string getdepartment() const { return department; }
    string getoffice() const { return office; }
    double getsalary() const { return salary; }
    const vector<string>& getteachingcourses() const { return teachingcourses; }
};

class course {
private:
    string coursecode;
    string coursename;
    int credits;
    professor* instructor;
    vector<student*> enrolledstudents;

    // вспомогательная функция для поиска студента по id
    student* find_student_by_id(const string& studentid) {
        for (size_t i = 0; i < enrolledstudents.size(); i++) {
            if (enrolledstudents[i]->getid() == studentid) {
                return enrolledstudents[i];
            }
        }
        return NULL;
    }

public:
    course(string code, string name, int cred) 
        : coursecode(code), coursename(name), credits(cred), instructor(NULL) {}
    
    void addstudent(student* student_ptr) {
        if (find(enrolledstudents.begin(), enrolledstudents.end(), student_ptr) == enrolledstudents.end()) {
            enrolledstudents.push_back(student_ptr);
            student_ptr->enrollcourse(coursecode);
            cout << "студент " << student_ptr->getname() << " добавлен на курс " << coursename << endl;
        } else {
            cout << "студент " << student_ptr->getname() << " уже записан на курс " << coursename << endl;
        }
    }
    
    void removestudent(const string& studentid) {
        student* found_student = find_student_by_id(studentid);
        if (found_student) {
            cout << "студент " << found_student->getname() << " удален с курса " << coursename << endl;
            found_student->dropcourse(coursecode);
            
            // удаляем из вектора
            vector<student*>::iterator it = find(enrolledstudents.begin(), enrolledstudents.end(), found_student);
            if (it != enrolledstudents.end()) {
                enrolledstudents.erase(it);
            }
        } else {
            cout << "студент с id " << studentid << " не найден на курсе " << coursename << endl;
        }
    }
    
    void setinstructor(professor* prof) {
        instructor = prof;
        if (prof) {
            prof->assigncourse(coursecode);
            cout << "преподаватель " << prof->getname() << " назначен на курс " << coursename << endl;
        }
    }
    
    void displaycourseinfo() const {
        cout << "код курса: " << coursecode << endl;
        cout << "название: " << coursename << endl;
        cout << "кредиты: " << credits << endl;
        if (instructor) {
            cout << "преподаватель: " << instructor->getname() << endl;
        } else {
            cout << "преподаватель: не назначен" << endl;
        }
        cout << "количество студентов: " << enrolledstudents.size() << endl;
        if (!enrolledstudents.empty()) {
            cout << "студенты: ";
            for (size_t i = 0; i < enrolledstudents.size(); i++) {
                cout << enrolledstudents[i]->getname();
                if (i < enrolledstudents.size() - 1) cout << " ";
            }
            cout << endl;
        }
    }
    
    string getcoursecode() const { return coursecode; }
    string getcoursename() const { return coursename; }
    int getcredits() const { return credits; }
    professor* getinstructor() const { return instructor; }
    const vector<student*>& getenrolledstudents() const { return enrolledstudents; }
};

class university {
private:
    string name;
    vector<universitymember*> members;
    vector<course*> courses;
    static int totaluniversities;

public:
    university(string n) : name(n) {
        totaluniversities++;
        cout << "создан университет: " << name << endl;
    }
    
    ~university() {
        // очищаем память
        for (size_t i = 0; i < members.size(); i++) {
            delete members[i];
        }
        for (size_t i = 0; i < courses.size(); i++) {
            delete courses[i];
        }
        totaluniversities--;
        cout << "университет " << name << " закрыт" << endl;
    }
    
    void addmember(universitymember* member) {
        members.push_back(member);
        cout << "добавлен член университета: " << member->getname() << endl;
    }
    
    void addcourse(course* crs) {
        courses.push_back(crs);
        cout << "добавлен курс: " << crs->getcoursename() << endl;
    }
    
    void displayallmembers() const {
        cout << "\nвсе члены университета " << name << endl;
        for (size_t i = 0; i < members.size(); i++) {
            members[i]->displayinfo();
            cout << endl;
        }
    }
    
    void displayallcourses() const {
        cout << "\nвсе курсы университета " << name << endl;
        for (size_t i = 0; i < courses.size(); i++) {
            courses[i]->displaycourseinfo();
            cout << endl;
        }
    }
    
    universitymember* findmember(const string& id) {
        for (size_t i = 0; i < members.size(); i++) {
            if (members[i]->getid() == id) {
                return members[i];
            }
        }
        return NULL;
    }
    
    course* findcourse(const string& code) {
        for (size_t i = 0; i < courses.size(); i++) {
            if (courses[i]->getcoursecode() == code) {
                return courses[i];
            }
        }
        return NULL;
    }
    
    static int gettotaluniversities() {
        return totaluniversities;
    }
    
    string getname() const { return name; }
    int getmembercount() const { return members.size(); }
    int getcoursecount() const { return courses.size(); }
};

int university::totaluniversities = 0;

int main() {
    
    // создаем университет
    university myuniversity("технический университет");
    
    // создаем студентов
    student* student1 = new student("иван иванов", "s001", "ivan@university.ru", "компьютерные науки", 2);
    student* student2 = new student("мария петрова", "s002", "maria@university.ru", "математика", 1);
    student* student3 = new student("петр сидоров", "s003", "petr@university.ru", "физика", 3);
    
    // создаем преподавателей
    professor* prof1 = new professor("доктор смирнов", "p001", "smirnov@university.ru", "компьютерные науки", "a101", 80000);
    professor* prof2 = new professor("доктор козлова", "p002", "kozlova@university.ru", "математика", "b205", 75000);
    
    // добавляем членов в университет
    myuniversity.addmember(student1);
    myuniversity.addmember(student2);
    myuniversity.addmember(student3);
    myuniversity.addmember(prof1);
    myuniversity.addmember(prof2);
    
    // создаем курсы
    course* course1 = new course("cs101", "введение в программирование", 4);
    course* course2 = new course("math201", "линейная алгебра", 3);
    course* course3 = new course("phy301", "квантовая механика", 5);
    
    // добавляем курсы в университет
    myuniversity.addcourse(course1);
    myuniversity.addcourse(course2);
    myuniversity.addcourse(course3);
    
    // назначаем преподавателей на курсы
    myuniversity.findcourse("cs101")->setinstructor(dynamic_cast<professor*>(myuniversity.findmember("p001")));
    myuniversity.findcourse("math201")->setinstructor(dynamic_cast<professor*>(myuniversity.findmember("p002")));
    
    // записываем студентов на курсы
    myuniversity.findcourse("cs101")->addstudent(dynamic_cast<student*>(myuniversity.findmember("s001")));
    myuniversity.findcourse("cs101")->addstudent(dynamic_cast<student*>(myuniversity.findmember("s002")));
    myuniversity.findcourse("math201")->addstudent(dynamic_cast<student*>(myuniversity.findmember("s002")));
    myuniversity.findcourse("math201")->addstudent(dynamic_cast<student*>(myuniversity.findmember("s003")));
        
    // отображаем всю информацию
    myuniversity.displayallmembers();
    myuniversity.displayallcourses();
    
    // демонстрация полиморфизма
    universitymember* member1 = myuniversity.findmember("s001");
    universitymember* member2 = myuniversity.findmember("p001");
    
    if (member1) {
        cout << "\nработа студента:" << endl;
        member1->work();
        cout << "роль: " << member1->getrole() << endl;
    }
    
    if (member2) {
        cout << "\nработа преподавателя:" << endl;
        member2->work();
        cout << "роль: " << member2->getrole() << endl;
    }
    
    // операции со студентами
    student* stud = dynamic_cast<student*>(myuniversity.findmember("s001"));
    if (stud) {
        stud->calculategpa(4.5);
        stud->enrollcourse("phy301");
    }
    
    // операции с преподавателями
    professor* prof = dynamic_cast<professor*>(myuniversity.findmember("p001"));
    if (prof) {
        prof->calculatesalary(5000);
        prof->assigncourse("cs201");
    }
    
    // статистика университета
    cout << "название: " << myuniversity.getname() << endl;
    cout << "количество членов: " << myuniversity.getmembercount() << endl;
    cout << "количество курсов: " << myuniversity.getcoursecount() << endl;
    cout << "всего университетов в системе: " << university::gettotaluniversities() << endl;
    
    // демонстрация удаления
    myuniversity.findcourse("math201")->removestudent("s003");
    
    // финальное отображение информации
    myuniversity.displayallcourses();
    
    return 0;
}
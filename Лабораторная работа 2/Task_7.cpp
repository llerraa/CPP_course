#include <iostream>
#include <string>
using namespace std;

struct Date {
    int day;
    int month;
    int year;
};


struct Student {
    string fio;
    Date birth_date;
    int grades[5];
};

// вывод информации о студенте - по константной ссылке (нельзя изменять, только читать)
void printStudent(const Student& s) {
    cout << "фио: " << s.fio << endl;
    cout << "дата рождения: " << s.birth_date.day << "." << s.birth_date.month << "." << s.birth_date.year << endl;
    cout << "оценки: ";
    for (int i = 0; i < 5; ++i) {
        cout << s.grades[i] << " ";
    }
}

// подсчет среднего балла студента
double getAverageRating(const Student& s) {
    int sum = 0;
    double average;
    for (int i = 0; i < 5; ++i) {
        sum += s.grades[i];
    }
    average = sum / 5.0;
    return average;
}

// список студентов, чей средний балл выше 4.0
void spisok(Student* arr_of_stud){ // указатель на массив student* arr_of_stud = arr
    double marks[4];
    for (int i = 0; i < 4; ++i) {
        marks[i] = getAverageRating(arr_of_stud[i]); //первый, второй... студент -> его средний балл
    }
    cout << "\n(промежуточно) все средние баллы: " << endl;
    for (int i = 0; i < 4; ++i) {
        cout << "имя: " << arr_of_stud[i].fio << ", ср.балл: " << marks[i] << "; " << endl;
    }
    cout << "\nтолько студенты, чей средний балл выше 4.0: " << endl;
    for (int i = 0; i < 4; ++i) {
        if (marks[i] > 4.0) {cout << "имя: " << arr_of_stud[i].fio << ", ср.балл: " << marks[i] << "; " << endl;}
    }
};
 

int main(){

    // создайте массив из 3-5 студентов и инициализируйте его данными (можно "вшитыми" в код)
    Student arr[4] = {
    { "иванов иван сергеевич", {10, 1, 2000}, {4, 4, 3, 5, 5}},
    { "сергеев михаил аркадьевич", {20, 2, 2002}, {5, 5, 5, 5, 5}},
    { "археев петр петрович", {30, 3, 2003}, {4, 4, 3, 3, 3}},
    { "матвеев егор александрович", {14, 4, 2004}, {2, 2, 3, 2, 2}},
    };

    cout << "\nвывод информации о студенте: " << endl;
    printStudent(arr[3]);
    
    cout << "\n\nсредняя оценка студента '" << arr[2].fio << "' равна: " << getAverageRating(arr[2]);
    
    cout << "\n\nсписок студентов, чей средний балл выше 4.0: " << endl;
    spisok(arr);

    return 0;
}
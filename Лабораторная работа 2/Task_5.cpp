#include <iostream>
#include <string>
using namespace std;

struct Book {
    string name;           
    string author;
    int year;
    double price;          
};

// реализуйте функцию void printBooks(Book* books, int size), которая выводит информацию о всех книгах
// Book* books = указатель books, указывать будет на элементы (структуры) массива, переданного при вызове
void printBooks(Book* books, int size) { // Book* books = arr ссылается на тот же массив
    cout << "\nвы в функции вывода инфы о всех книгах" << endl;
    for (int i = 0; i < size; ++i) {
        cout << "\nкнига номер: " << i+1 << endl;
        // books[i] - адрес 
        // *books[i] - значение (структура под номером i) 
        cout << "название: " << (*(books+i)).name << endl;
        cout << "автор: " << (*(books+i)).author << endl;
        cout << "год: " << (*(books+i)).year << endl;
        cout << "цена: " << (*(books+i)).price << endl;
    }
};

// напишите функцию, которая находит и выводит самую дорогую книгу в массиве
void top_price(Book* books, int size) {
    double stoimost = 0;
    string name;
    for (int i = 0; i < size; ++i) {
        if ( (*(books+i)).price > stoimost) { 
            stoimost = (*(books+i)).price;
            name = (*(books+i)).name;
        }
    }
    cout << "\nсамая дорогая книга: " << name << " \nи она стоит: " << stoimost << endl;
}

int main(){

    // запросите у пользователя количество книг N в библиотеке
    int N;
    cout << "какое количество книг в библиотеке?(БОЛЬШЕ НУЛЯ) ";
    cin >> N;

    // динамически выделите память под массив из N структур Book
    // указатель arr типа Book =  массив из N объектов типа Book
    // это указатель, который способен хранить адрес объекта Book
    Book* arr = new Book[N];
    cout << "\nсоздали массив размера: " << N << endl;

    // заполните массив данными, введенными пользователем
    for (int i = 0; i < N; ++i) {
        cout << "\nкнига номер: " << i+1 << endl;

        cout << "введите название (ОДНО СЛОВО): ";
        cin >> arr[i].name; // arr[i].name = (*(arr+i)).name (то есть [] сразу разыменовывают)
        
        cout << "введите ТОЛЬКО ИМЯ автора: ";
        cin >> arr[i].author;
        
        cout << "введите год: ";
        cin >> arr[i].year;
        
        cout << "введите цену: ";
        cin >> arr[i].price;
    }
    
    printBooks(arr, N);
    top_price(arr, N);

    // не забудьте освободить динамически выделенную память
    delete[] arr;

    return 0;
}
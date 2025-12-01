#include <iostream>
#include <string>
using namespace std;

struct Book {
    string name;           
    string author;
    int year;
    double price;          
};

// сортирует массив книг по году издания (по возрастанию) пузырьковой сортировкой
void sortBooksByYear(Book* books, int size) { // Book* books = arr 
    
    // пузырьковая сортировка
    for (int i = 0; i < size - 1; ++i) { // делаем так (size-1) раз (потому что при пятом проходе последний элемент уже на своем месте)
        for (int j = 0; j < size - i - 1; ++j) { // проходим весь массив, но с каждым разом с конца берем на i меньше элементов, так как они уже "всплыли"
            if ( books[j].year > books[j+1].year ) { // если левое больше правого, то меняем местами
                Book tmp;
                tmp = books[j];
                books[j] = books[j+1];
                books[j+1] = tmp;
            }
        }
    }
    
    cout << "\n\nкниги и года по возрастанию: " << endl;
    for (int i = 0; i < size; ++i) {
        cout << books[i].name << "; " << books[i].year << endl;
    }
}

// возвращает указатель на первую найденную книгу указанного автора
// если книга не найдена, функция должна возвращать nullptr
Book* findBookByAuthor(Book* books, int size, const string& author) { 
    // Book* books = arr
    // const string& author = cin_author
    for (int i = 0; i < size; ++i) {
        if (books[i].author == author) { 
            return &books[i];  // сразу возвращаем первую найденную
        }
    }
    return nullptr;
}

int main(){

    // динамически выделяю память под массив из 5 структур Book
    // указатель arr типа Book =  массив из 5 объектов типа Book
    // это указатель, который способен хранить адрес объекта Book
    Book* arr = new Book[5];

    // заполняю массив данными

    arr[0].name = "Война и мир";
    arr[0].author = "Лев Толстой";
    arr[0].year = 1869;
    arr[0].price = 150.5;
    
    arr[1].name = "Преступление и наказание";
    arr[1].author = "Фёдор Достоевский";
    arr[1].year = 1866;
    arr[1].price = 120.0;
    
    arr[2].name = "Мастер и Маргарита";
    arr[2].author = "Михаил Булгаков";
    arr[2].year = 1967;
    arr[2].price = 180.3;
    
    arr[3].name = "Евгений Онегин";
    arr[3].author = "Александр Пушкин";
    arr[3].year = 1833;
    arr[3].price = 90.7;
    
    arr[4].name = "Отцы и дети";
    arr[4].author = "Иван Тургенев";
    arr[4].year = 1862;
    arr[4].price = 110.2;

    sortBooksByYear(arr, 5);

    string cin_author;
    cout << "\nкакого автора ищем? ";
    getline(cin, cin_author);  // ✅ читаем всю строку с пробелами
    Book* otvet = findBookByAuthor(arr, 5, cin_author);  // вернет Book* ptr_book = books[i]
    cout << "автор '" << cin_author << "' написал книгу " << (*otvet).name; // значение указателя

    // освободила память
    delete[] arr;
    return 0;
}
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Book {
private:
    string title;
    string author;
    string isbn;
    int year;
    bool isAvailable;

public:
    Book(string t, string a, string i, int y, bool ia) : title(t), author(a), isbn(i), year(y), isAvailable(ia) {}
    
    string GetTitle() const {
        return title;
    }

    string GetAuthor() const {
        return author;
    }

    string GetIsbn() const {
        return isbn;
    }

    int GetYear() const {
        return year;
    }

    bool GetAvailable() const {
        return isAvailable;
    }

    void SetTitle(string t) {
        title = t;
    }

    void SetAuthor(string a) {
        author = a;
    }

    void SetIsbn(string i) {
        isbn = i;
    }

    void SetYear(int y) {
        year = y;
    }

    void SetAvailable(bool ia) {
        isAvailable = ia;
    }
    
    void borrow() {
        if (isAvailable) {
            cout << "\nвы забрали книгу " << title << " из библиотеки" << endl;
            isAvailable = false;
        } else {
            cout << "книга с названием " << title << " уже на руках, выбери другую" << endl;
        }
    }

    void returnBook() {
        if (isAvailable) {
            cout << "\nвы вернули книгу " << title << ", но она уже есть в библиотеке" << endl;
        } else {
            cout << "\nвы вернули книгу с названием " << title << " в библиотеку" << endl;
            isAvailable = true;
        }
    }

    void displayInfo() const {
        cout << "\nназвание: " << title << endl;
        cout << "автор: " << author << endl;
        cout << "номер: " << isbn << endl;
        cout << "год: " << year << endl;
        cout << "доступность: " << (isAvailable ? "доступна" : "на руках") << endl;
    }
};

class Library {
private:
    string name;
    string address;
    vector<Book> books;

public:
    Library(string n, string addr) : name(n), address(addr) {}
    
    void addBook(const Book& book) {
        books.push_back(book);
        cout << "книга '" << book.GetTitle() << "' добавлена" << endl; 
    }
    
    void removeBook(const string& isbn) {
        for (auto i = books.begin(); i != books.end(); ++i) {
            if (i->GetIsbn() == isbn) {
                if (i->GetAvailable()) {
                    cout << "\nкнига номер " << isbn << " удалена из библиотеки" << endl;
                    books.erase(i);
                } else {
                    cout << "\nкнига не удалена (возможно она на руках)" << endl;
                }
                return;
            }
        }
        cout << "\nкнига с номером " << isbn << " не найдена" << endl;
    }    
    
    void findBook(const string& title) const {
        bool found = false;
        for (const Book& book : books) {
            if (book.GetTitle() == title) {
                cout << "\nкнига найдена!" << endl;
                book.displayInfo();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "\nкнига не найдена" << endl;
        }
    }
    
    void borrowBook(const string& isbn) {
        for (Book& book : books) {
            if (book.GetIsbn() == isbn) {
                book.borrow(); // метод книги
                return;
            }
        }
        cout << "\nкнига с номером " << isbn << " не найдена" << endl;
    }
    
    void returnBook(const string& isbn) {
        for (Book& book : books) {
            if (book.GetIsbn() == isbn) {
                book.returnBook(); // метод книги
                return;
            }
        }
        cout << "\nкнига с номером " << isbn << " не найдена" << endl;
    }
    
    void displayAllBooks() const {
        cout << "\n все книги в библиотеке" << endl;
        for (const Book& book : books) {
            book.displayInfo();
        }
    }
    
    void displayAvailableBooks() const {
        cout << "\nдоступные книги" << endl;
        bool found = false;
        for (const Book& book : books) {
            if (book.GetAvailable()) {
                book.displayInfo();
                found = true;
            }
        }
        if (!found) {
            cout << "нет доступных книг" << endl;
        }
    }
};

int main() {
    Book book1("Война и мир", "Лев Толстой", "1000", 1867, true);
    Book book2("Мастер и Маргарита", "Михаил Булгаков", "1001", 1967, true);
    Book book3("1984", "Джордж Оруэлл", "1002", 1949, true);
    Book book4("Преступление и наказание", "Федор Достоевский", "1003", 1866, true);
    Book book5("Гарри Поттер и философский камень", "Джоан Роулинг", "1004", 1997, true);

    Library lib1("Центральная городская библиотека", "ул. Книжная, 15");

    lib1.addBook(book1);
    lib1.addBook(book2);
    lib1.addBook(book3);
    lib1.addBook(book4);
    lib1.addBook(book5);
    
    lib1.displayAllBooks();
    
    lib1.borrowBook("1001");
    lib1.borrowBook("1001"); // попытка взять уже взятую книгу
    
    lib1.findBook("Гарри Поттер и философский камень");
    
    lib1.returnBook("1001"); 
    lib1.returnBook("1001"); // попытка вернуть книгу, которую не брали
    
    lib1.displayAvailableBooks();
    
    lib1.removeBook("1004");
    lib1.removeBook("1005"); // несуществующая книга

    return 0;
}
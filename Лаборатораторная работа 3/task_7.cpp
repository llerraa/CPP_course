#include <iostream>
#include <string>
using namespace std;

class Complex {
private:
    double real;
    double imaginary;

public:
    
    Complex(double r = 0, double i = 0) : real(r), imaginary(i) {}
    
    // TODO: Геттеры и сеттеры
    double getReal() const { return real; }
    double getImaginary() const { return imaginary; }
    
    void setReal(double r) { real = r; }
    void setImaginary(double i) { imaginary = i; }
    
    // TODO: Перегрузить операторы:
    // - Complex operator+(const Complex& other) const
    // - Complex operator-(const Complex& other) const
    // - Complex operator*(const Complex& other) const
    // - bool operator==(const Complex& other) const
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imaginary - other.imaginary);
    }
    
    Complex operator*(const Complex& other) const {
        // (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
        return Complex(real * other.real - imaginary * other.imaginary,
                      real * other.imaginary + imaginary * other.real);
    }
    
    bool operator==(const Complex& other) const {
        return real == other.real && imaginary == other.imaginary;
    }
    
    
    // TODO: Сделать дружественными:
    // - friend ostream& operator<<(ostream& os, const Complex& c)
    // - friend istream& operator>>(istream& is, Complex& c)
    friend ostream& operator<<(ostream& os, const Complex& c);
    friend istream& operator>>(istream& is, Complex& c);
    
    void display() const {
        cout << real << " + " << imaginary << "i" << endl;
    }
};

// Дружественная функция для вывода
ostream& operator<<(ostream& os, const Complex& c) {
    if (c.imaginary >= 0) {
        os << c.real << " + " << c.imaginary << "i";
    } else {
        os << c.real << " - " << -c.imaginary << "i";
    }
    return os;
}

// Дружественная функция для ввода
istream& operator>>(istream& is, Complex& c) {
    cout << "введите действительную часть: ";
    is >> c.real;
    cout << "введите мнимую часть: ";
    is >> c.imaginary;
    return is;
}

int main() {
    // Показать ввод/вывод через перегруженные операторы << и >>

    // TODO: Создать несколько комплексных чисел
    Complex c1(3.0, 4.0);
    Complex c2(1.5, -2.5);
    Complex c3;
    
    cout << "c1 = " << c1 << endl;
    cout << "c2 = " << c2 << endl;
    cout << "c3 = " << c3 << endl;
    
    // Продемонстрировать работу перегруженных операторов
    // арифметические операции
    Complex sum = c1 + c2;
    Complex diff = c1 - c2;
    Complex product = c1 * c2;
    
    cout << "c1 + c2 = " << sum << endl;
    cout << "c1 - c2 = " << diff << endl;
    cout << "c1 * c2 = " << product << endl;
    
    // операци с присваиванием
    c3 = c1 + c2;
    cout << "c3 = c1 + c2 = " << c3 << endl;
    
    c3 = c1 * c2;
    cout << "c3 = c1 * c2 = " << c3 << endl;
    
    // сравнение
    Complex c4(3.0, 4.0);
    cout << "c1 = " << c1 << endl;
    cout << "c4 = " << c4 << endl;
    cout << "c1 == c4: " << (c1 == c4 ? "true" : "false") << endl;
    cout << "c1 == c2: " << (c1 == c2 ? "true" : "false") << endl;
    
    // цепочка операций
    Complex result = c1 + c2 * c3;
    cout << "c1 + c2 * c3 = " << result << endl;
    
    result = (c1 + c2) * c3;
    cout << "(c1 + c2) * c3 = " << result << endl;
    
    // ввод через перегруженный оператор >>
    Complex c5;
    cin >> c5;
    cout << "вы ввели: " << c5 << endl;
    
    // вывод в разных форматах
    Complex positive(2.0, 3.0);
    Complex negative(2.0, -3.0);
    Complex zeroImaginary(5.0, 0.0);
    Complex zeroReal(0.0, 7.0);
    
    cout << "\npositive = " << positive << endl;
    cout << "negative = " << negative << endl;
    cout << "zeroImaginary = " << zeroImaginary << endl;
    cout << "zeroReal = " << zeroReal << endl;
    
    return 0;
}
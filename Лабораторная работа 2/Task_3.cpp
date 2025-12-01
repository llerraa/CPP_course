#include <iostream>
#include <string>
using namespace std;

struct Complex {
    float real;           // действительная часть
    float imag;           // мнимая часть (коэффициент перед i)
};

// сложение
Complex add(const Complex& a, const Complex& b) {
    Complex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return result;
}

// вычитание
Complex subtract(const Complex& a, const Complex& b) {
    Complex result;
    result.real = a.real - b.real;
    result.imag = a.imag - b.imag;
    return result;
}

// умножение
Complex multiply(const Complex& a, const Complex& b) {
    Complex result;
    // (a + bi) * (c + di) = ac + adi + bci + bdi² 
    // = (ac - bd) + (ad + bc)i  (т.к. i² = -1)
    result.real = a.real * b.real - a.imag * b.imag;
    result.imag = a.real * b.imag + a.imag * b.real;
    return result;
}

// вывод в форме (a + bi)
void print(const Complex& c) {
    cout << "(" << c.real;
    if (c.imag >= 0) {
        cout << " + " << c.imag << "i)";
    } else {
        cout << " - " << -c.imag << "i)";
    }
    cout << endl;
}

int main() {
    // создаю переменные типа Complex 
    // 3 + 2i
    // 1 - 4i
    Complex complex1;
    Complex complex2;
    
    // инициализация полей структур
    complex1.real = 3;
    complex1.imag = 2;

    complex2.real = 1;
    complex2.imag = -4;
    
    // демонстрация работы всех функций
    cout << "complex1 = ";
    print(complex1);
    
    cout << "complex2 = ";
    print(complex2);
    
    cout << "сложение: ";
    print(add(complex1, complex2));
    cout << "вычитание: ";
    print(subtract(complex1, complex2));
    cout << "умножение: ";
    print(multiply(complex1, complex2));
    
    return 0;
}
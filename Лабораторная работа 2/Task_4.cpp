#include <iostream>
using namespace std;

// пытается обменять значения (не получится)
void swapValues_1(int a, int b) { // a = m, b = n
    cout << "функция обмена с помощью значений" << endl;
    cout << "до обмена первое значение = " << a << endl;
    cout << "до обмена второе значение = " << b << endl;
    int temp;
    temp = a; 
    a = b; 
    b = temp; 
    cout << "после обмена первое значение = " << a << endl;
    cout << "после обмена второе значение = " << b << endl;
    cout << endl;
}

// обменивает значения с помощью указателей
void swapValues_2(int* a, int* b) { // int* a = &m, int*b = &n
    cout << "функция обмена с помощью указателей" << endl;
    cout << "до обмена первое значение = " << *a << endl;
    cout << "до обмена второе значение = " << *b << endl;
    int temp = *a; // temp = ЗНАЧЕНИЮ a
    *a = *b; // обмен значениями 
    *b = temp; // обмен значениями 
    cout << "после обмена первое значение = " << *a << endl;
    cout << "после обмена второе значение = " << *b << endl;
    cout << endl;
}

// обменивает значения с помощью ссылок
void swapValues_3(int& a, int& b) { // int& a = m, int& b = n
    cout << "функция обмена с помощью ссылок" << endl;
    cout << "до обмена первое значение = " << a << endl;
    cout << "до обмена второе значение = " << b << endl;
    int temp;
    temp = a; 
    a = b; 
    b = temp;  
    cout << "после обмена первое значение = " << a << endl;
    cout << "после обмена второе значение = " << b << endl << endl;
}

int main() {

    // В main покажите работу всех трех функций на примере двух целых чисел
    int m, n;
    cout << "введите первое целое число:" << endl;
    cin >> m;
    cout << "введите второе целое число:" << endl;
    cin >> n;
    cout << endl;

    swapValues_1(m, n);
    cout << "m = " << m << "; n = " << n << endl << endl;
    swapValues_2(&m, &n); // функция принимает указатели, поэтому передаю ссылки на память
    cout << "m = " << m << "; n = " << n << endl << endl;
    swapValues_3(m, n);
    cout << "m = " << m << "; n = " << n << endl << endl;

    return 0;
}
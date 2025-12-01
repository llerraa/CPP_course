#include <iostream>
#include <string>
using namespace std;

// заполните массив из 10 чисел последовательностью Фибоначчи - последовательность чисел, где каждое следующее число равно сумме двух предыдущих.
// 1,1,2,3,5,8,13,21,34,55 
void zapolnenie(int* array, int size) { // int* array = ptr_arr (тоже ссылается на array)
    int* tmp = array; // указатель который остался на начале, чтобы потом сделать cout
    *array = 1;
    array++;
    *array = 1;
    array++;
    for (int i = 2; i < size; ++i) {
        // *(array+i) = ; // разыменовывание аналог []
        *array = (*(array - 1)) + (*(array - 2)); 
        array++;
    }

    cout << "\nзаполненный массив:" << endl;
    for (int i = 0; i < size; ++i) {
        cout << *tmp << " ";
        tmp++;
    }
}

// найдите сумму всех элементов массива.
int summa(int* array, int size) { // int* array = ptr_arr (тоже ссылается на array)
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += *array;
        array++;
    }
return sum;
}

// найдите минимальный элемент в массиве.
int min(int* array, int size) { // int* array = ptr_arr (тоже ссылается на array)
    int min = *array;
    for (int i = 0; i < size; ++i) {
        // cout << *array << " " << *(array+1) << endl;
        if ((*array) < min) { min = *array; }
        array++;
    }
return min;
}

// скопируйте содержимое первого массива во второй массив в обратном порядке.
void copy(int* array, int size) { // int* array = ptr_arr (тоже ссылается на array)
    int* new_arr = new int[size];
    int* tmp = new_arr; // указатель который остался на начале, чтобы потом сделать cout
    int* tmp_for_delete = new_arr; // указатель который остался на начале, чтобы потом сделать delete

    for (int i = 0; i < size; ++i) {
        // cout << *(array+(size-i-1)) << endl;
        *new_arr = *(array+(size-i-1));
        new_arr++;
    }
    for (int i = 0; i < size; ++i) {
        cout << *tmp << " ";
        tmp++;
    }

    delete[] tmp_for_delete; // new_arr уже сдвинулся => удаляю через указатель, который ссылается на начало
}

int main() {
    int array[10];
    int N = sizeof(array) / sizeof(array[0]); // получу кол-во элементов (размер общ / размер одного)
    // cout << N;

    int* ptr_arr = array;
    
    zapolnenie(ptr_arr, N); // передала ptr_arr = адрес array

    cout << "\n\nсумма всех элементов массива: " << summa(ptr_arr, N) << endl;
    cout << "\nсамый минимальный элемент массива: " << min(ptr_arr, N) << endl;
    
    cout << "\nновый массив: \n";
    copy(ptr_arr, N); // передала ptr_arr = адрес array

    return 0;
}
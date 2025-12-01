#include <iostream>
#include <string>
using namespace std;
 
void arrayInfo(int* arr, int size) { // принимаю указатель int* arr = new_array (ссылается на ту же память, что и new_array)
    cout << "\nвыводим информацию о массиве:" << endl;
    cout << "размер массива: " << size << endl; // или можно было вычислить sizeof(arr)/sizeof(arr[0]) => общая сумма байтов / на сумму байтов первого
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    cout << "сумма элементов: " << sum << endl;
    cout << "первый элемент: " << arr[0] << endl;
    cout << "последний элемент: " << arr[size-1] << endl;

}

int main(){

    cout << "давайте заполним массив!" << endl;
    int N;
    cout << "введите размер массива: ";
    cin >> N;

    int* new_array = new int[N]; // указатель на динамический массив
    for (int i = 0; i < N; ++i) {
        cout << i << "-е число: ";
        cin >> new_array[i];
    }
    cout << "ваш массив заполнен, вы супер" << endl;
    arrayInfo(new_array, N);

    // освободила память
    delete[] new_array;
    
    return 0;
}
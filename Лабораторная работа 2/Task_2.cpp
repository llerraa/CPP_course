#include <iostream>
using namespace std;

char* zapolnenie(char arr[]) { // arr[] = ptr_mysrting
    cout << "введите строку: " << endl;
    cin.getline(arr, 20);
    return arr; //указатель на arr
}

int dlina_stroki(char arr[], int size) { 
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i] == '\0') {
            break;
        }
        sum += 1;
    }
    return (sum);
} 

char* replacement(char arr[], int size) { // arr[] = ptr_mysrting ,  final_size = 5
    int seredinka = size / 2; // 2 (дробная часть отбрасывается, не округляется)
    char word_1;
    char word_2;
    // h e l l o 
    // 0 1 2 3 4
    for (int i = 0; i < seredinka; ++i) { // 1
        word_1 = arr[i]; // 0
        word_2 = arr[size-(i+1)];
        // cout << "i = " << i << " [size-(i+1)] = " << size-(i+1) << "  arr[i] = " << arr[i] << " arr[size-(i+1)] = " << arr[size-(i+1)] << endl;
        arr[i] = word_2;
        arr[size-(i+1)] = word_1;
        // cout << "arr на данный момент: " << endl;
        // for (int i = 0; i < size; ++i) {
        //     cout << arr[i] << endl;
        // }
    }
    return arr;   //указатель на arr
}

int simvol(char arr[], int size, char simvol) { // arr[] = ptr_mysrting ,  final_size = 5
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i] == simvol) { sum += 1;}
    }
    return sum;
}

int main() {

    char mysrting[20];
    char* ptr_mysrting = mysrting;

    // Пользователь вводит строку:
    zapolnenie(ptr_mysrting); // вернет char* arr (помним, что arr[] = ptr_mysrting) => ptr_mysrting = char* arr (указывают на одну и ту же ячейку памяти)
    
    // проверка вывода
    // cout << *ptr_mysrting << endl; // с char[] указатель ведет себя особенно, поэтому при разыменовывании выводит первую ячейку массива
    cout << "вы ввели: " << ptr_mysrting << endl; // с char[] указатель ведет себя особенно, поэтому ptr_mysrting выводит строку, а не память
    
    // Программа определяет длину строки:
    int dlina = sizeof(mysrting);
    cout << "sizeof массива (нужна для длины строки) = " << dlina << endl;
    int final_size = dlina_stroki(mysrting, dlina);
    cout << "длина строки равна: " << final_size << endl;

    // Программа переворачивает строку на месте (in-place), т.е. не создавая новый массив
    replacement(ptr_mysrting, final_size);
    cout << "новая строка равна: " << ptr_mysrting << endl; // вернет char* arr (помним, что arr[] = ptr_mysrting) => ptr_mysrting = char* arr (указывают на одну и ту же ячейку памяти)
    
    // Программа подсчитывает количество вхождений определенного символа (также введенного пользователем) в строку
    cout << "какой символ посчитать по количеству? ";
    char n;
    cin >> n;
    cout << "символ встречается " << simvol(ptr_mysrting, final_size, n) << " раз" << endl;
    
    return 0;

}
#include <iostream>
using namespace std;

// функция возвращает указатель
double* temperature(int size) {
    double* arr = new double[size]; // создаю указатель на массив
    for (int i = 0; i < size; ++i) {
        cout << "Какая температура была в день номер " << i+1 << "? ";
        cin >> arr[i];
    }
    return arr; // возвращаю указатель на созданный массив // double* arr
}

double counter(double* arr, int days) { // принимаю указатель double* arr = day_temp (ссылается на ту же память = 0x1000)
    double sum = 0;
    cout << "считаем среднюю темпераутуру за период!" << endl;
    for (int i = 0; i < days; ++i) {
        sum += arr[i];
    }
    double otvet = sum / days;
    return otvet;
}

double min_elem(double* arr, int days) {
    double vrem_min = arr[0];
    for (int i = 0; i < days; ++i) {
        if (arr[i] < vrem_min) { vrem_min = arr[i];}
    }
    return vrem_min;
}

double max_elem(double* arr, int days) {
    double vrem_max = arr[0];
    for (int i = 0; i < days; ++i) {
        if (arr[i] > vrem_max) { vrem_max = arr[i];}
    }
    return vrem_max;
}

int kol_vo(double* arr, int days, double srednya){
    int kol_vo = 0;
    for (int i = 0; i < days; ++i) {
        if ( arr[i] < srednya) { kol_vo += 1;}
    }
    return kol_vo;
}

int main() {
    int N;
    cout << "введите количество дней для анализа (БОЛЬШЕ НУЛЯ): "; // если будет = 0, то будет деление на ноль дальше
    cin >> N;
    
    double* day_temp = temperature(N);
    // cout << day_temp << endl;
    // temperature(N) вернула 0x1000 (например)
    // day_temp = arr (тоже ссылается на эту память = 0x1000)

    cout << "вы ввели следующие данные: " << endl;
    for (int i = 0; i < N; ++i) {
        cout << i+1 << " день: "; 
        cout << day_temp[i] << " градусов " << endl;
    } 

    double sred_temp = 0;
    sred_temp = counter(day_temp, N); // передаю указатель на массив и кол-во дней
    cout << "средняя температура за период: " << sred_temp << endl;
    
    double min;
    min = min_elem(day_temp, N);
    
    double max;
    max = max_elem(day_temp, N);
    
    cout << "минимальная температура: " << min << endl;
    cout << "максимальная температура: " << max << endl; 

    // количество дней, когда температура была ниже средней
    cout << "количество дней, когда температура была ниже средней: " << kol_vo(day_temp, N, sred_temp);

    delete[] day_temp; // освободила память
    return 0;
}
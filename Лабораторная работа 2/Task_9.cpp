#include <iostream>
#include <string>
using namespace std;

struct Account {
    int id;
    double balance;
};

//увеличивает баланс счета на указанную сумму, используя указатель.
void deposit(Account* acc, double amount) { // Account* acc = Account* ptr_account1   =>  тоже указывает на адрес структуры account1
    // cout << "(*acc).balance = " << (*acc).balance << endl;
    // cout << "acc = " << acc << endl;
    if (amount > 0) {
            (*acc).balance += amount; // * значение указателя
            cout << "значение баланса для аккаунта " << (*acc).id << " увеличено на " << amount << endl;
            cout << "нынешнее значение баланса = " << (*acc).balance << endl;
        } else {
            cout << "ошибка: сумма депозита должна быть положительной" << endl;
        }
}

// уменьшает баланс счета на указанную сумму, используя ссылку. 
// должна проверять, достаточно ли средств на счете.
void withdraw(Account& acc, double amount) { // Account& acc = account1 (ссылка указывает на память account1)
    // благодаря ссылке работаем как с обычной переменной
    if (acc.balance < amount) { cout << "недостаточно средств для снятия" << endl;}
    else {
        acc.balance -= amount; // * значение указателя
        cout << "значение баланса для аккаунта " << acc.id << " уменьшено на " << amount << endl;
        cout << "нынешнее значение баланса = " << acc.balance << endl;
    }
}

int main(){
    Account account1;
    account1.id = 1111;
    account1.balance = 150.5;
    
    double summa_1 = 0;
    cout << "сколько денег хотим положить? ";
    cin >> summa_1;

    Account* ptr_account1 = &account1; //создаю указатель на адрес account1 и передаю в функцию
    deposit(ptr_account1, summa_1);

    double summa_2 = 0;
    cout << "сколько денег хотим забрать? ";
    cin >> summa_2;
    
    withdraw(account1, summa_2);

    return 0;
}
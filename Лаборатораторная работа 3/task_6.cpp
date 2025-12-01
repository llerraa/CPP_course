#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountNumber;
    string ownerName;
    double balance;
    static int totalAccounts;           // Общее количество счетов
    static double totalBankBalance;     // Общий баланс банка
    const double MIN_BALANCE = 10.0;    // Минимальный баланс

public:
    // Конструктор с параметрами
    // В конструкторе увеличивать totalAccounts и добавлять баланс к totalBankBalance
    BankAccount(string accNum, string owner, double initialBalance) 
        : accountNumber(accNum), ownerName(owner), balance(initialBalance) {
        totalAccounts++;
        totalBankBalance += initialBalance;
        cout << "создали счёт номер: " << accountNumber << " для " << ownerName << endl;
    }
    
    // Деструктор
    // В деструкторе уменьшать totalAccounts и вычитать баланс из totalBankBalance
    ~BankAccount() {
        totalAccounts--;
        totalBankBalance -= balance;
        cout << "закрыли счёт номер: " << accountNumber << endl;
    }
    
    // TODO: Реализовать методы:
    // - deposit(double amount)
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            totalBankBalance += amount;
            cout << "внесли сумма: " << amount << " на счет номер: " << accountNumber << endl;
        } else {
            cout << "сумма для внесения должна быть положительной" << endl;
        }
    }
    
    // - withdraw(double amount) с проверкой минимального баланса
    void withdraw(double amount) {
        if (amount > 0) {
            if (balance - amount >= MIN_BALANCE) {
                balance -= amount;
                totalBankBalance -= amount;
                cout << "сняли сумма: " << amount << " со счёта: " << accountNumber << endl;
            } else {
                cout << "недостаточно средств, текущий баланс: " << balance << endl;
                cout << "минимальный баланс, который можно оставить: " << MIN_BALANCE << endl;
            }
        } else {
            cout << "сумма для снятия должна быть положительной" << endl;
        }
    }
    
    // - displayAccountInfo() const
    void displayAccountInfo() const {
        cout << "\nинформация о счёте: " << endl;
        cout << "номер счета: " << accountNumber << endl;
        cout << "владелец: " << ownerName << endl;
        cout << "баланс: " << balance << endl;
        cout << "минимальный баланс: " << MIN_BALANCE << endl;
    }
    
    // TODO: Статические методы:
    // - static int getTotalAccounts()
    static int getTotalAccounts() {
        return totalAccounts;
    }
    
    // - static double getTotalBankBalance()
    static double getTotalBankBalance() {
        return totalBankBalance;
    }
    
    // - static double getAverageBalance()
    static double getAverageBalance() {
        if (totalAccounts > 0) {
            return totalBankBalance / totalAccounts;
        }
        return 0.0;
    }
    
    // Геттеры для тестирования
    string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
};

// Инициализация статических переменных
int BankAccount::totalAccounts = 0;
double BankAccount::totalBankBalance = 0.0;

int main() {
    
    cout << "\nначальная статистика:" << endl;
    cout << "всего счетов: " << BankAccount::getTotalAccounts() << endl;
    cout << "общий баланс банка: " << BankAccount::getTotalBankBalance() << endl;
    cout << "средний баланс: " << BankAccount::getAverageBalance() << endl;
    
    // TODO: Создать несколько счетов
    // Продемонстрировать работу статических методов
    // Показать, что статические переменные общие для всех объектов
    BankAccount account1("ACC001", "Иван Иванов", 1000.0);
    BankAccount account2("ACC002", "Петр Петров", 500.0);
    BankAccount account3("ACC003", "Мария Сидорова", 1500.0);
    
    cout << "всего счетов: " << BankAccount::getTotalAccounts() << endl;
    cout << "общий баланс банка: " << BankAccount::getTotalBankBalance() << endl;
    cout << "средний баланс: " << BankAccount::getAverageBalance() << endl;
    
    //операции со счетами
    account1.deposit(200.0);
    account2.withdraw(100.0);
    account3.withdraw(1490.0); // Попытка снять слишком много
    
    account1.displayAccountInfo();
    account2.displayAccountInfo();
    account3.displayAccountInfo();
    
    //после операций
    cout << "\nстатистика после операций:" << endl;
    cout << "всего счетов: " << BankAccount::getTotalAccounts() << endl;
    cout << "общий баланс банка: " << BankAccount::getTotalBankBalance() << endl;
    cout << "средний баланс: " << BankAccount::getAverageBalance() << endl;
    
    //работа деструктора
    {
        BankAccount tempAccount("TEMP001", "Временный", 300.0);
        cout << "временных счетов: " << BankAccount::getTotalAccounts() << endl;
        cout << "общий баланс с временным счетом: " << BankAccount::getTotalBankBalance() << endl;
    } 
    
    cout << "\nпосле закрытия временного счета:" << endl;
    cout << "всего счетов: " << BankAccount::getTotalAccounts() << endl;
    cout << "общий баланс банка: " << BankAccount::getTotalBankBalance() << endl;
    
    return 0;
}
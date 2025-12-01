#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Vehicle {
protected:
    string brand;
    string model;
    int year;
    double fuelLevel;

public:
    Vehicle(string b, string m, int y) : brand(b), model(m), year(y), fuelLevel(100) {}
    virtual ~Vehicle() {}
    
    // TODO: Сделать класс абстрактным с чисто виртуальными методами:
    // - startEngine()
    // - stopEngine()
    // - refuel(double amount)
    virtual void startEngine() = 0;
    virtual void stopEngine() const = 0;
    virtual void refuel(double amount) = 0;

    virtual void displayInfo() const {
        cout << brand << " " << model << " (" << year << ")" << endl;
        cout << "Уровень топлива: " << fuelLevel << "%" << endl;
    }
    
    double getFuelLevel() const { 
        return fuelLevel; 
    }
    
    void setFuelLevel(double level) { 
        if (level >= 0 && level <= 100) fuelLevel = level; 
    }
};

class Car : public Vehicle {
private:
    int doors;
    string transmission;

public:
    Car(string b, string m, int y, int d, string trans) 
        : Vehicle(b, m, y), doors(d), transmission(trans) {}
    
    // TODO: Реализовать чисто виртуальные методы
    void startEngine() override {
        cout << "двигатель машины заведен! тратим бензин" << endl;
        double level_after_start = getFuelLevel() - 15;
        setFuelLevel(level_after_start);
    }

    void stopEngine() const override {
        cout << "двигатель машины выключен!" << endl;
    }

    void refuel(double amount) override {
        cout << "\nвы хотите заправить авто на " << amount << endl;
        double level_after_refuel = getFuelLevel() + amount;
        setFuelLevel(level_after_refuel);
        cout << "теперь ваш уровень топлива в авто " << getFuelLevel() << endl << endl;
    }

    void displayInfo() const override {
        cout << brand << " " << model << " (" << year << ")" << " " << doors << " " << transmission << endl;
        cout << "Уровень топлива: " << fuelLevel << "%" << endl;
    }
};

class Motorcycle : public Vehicle {
private:
    bool hasFairing;

public:
    Motorcycle(string b, string m, int y, bool fairing) 
        : Vehicle(b, m, y), hasFairing(fairing) {}
    
    // TODO: Реализовать чисто виртуальные методы
    void startEngine() override {
        cout << "двигатель мото заведен! тратим бензин" << endl;
        double level_after_start = getFuelLevel() - 15;
        setFuelLevel(level_after_start);
    }

    void stopEngine() const override {
        cout << "двигатель мото выключен!" << endl;
    }

    void refuel(double amount) override {
        cout << "\nвы хотите заправить мото на " << amount << endl;
        double level_after_refuel = getFuelLevel() + amount;
        setFuelLevel(level_after_refuel);
        cout << "теперь ваш уровень топлива в мото " << getFuelLevel() << endl << endl;
    }
    
    void displayInfo() const override {
        cout << brand << " " << model << " (" << year << ")" << " " << hasFairing << endl;
        cout << "Уровень топлива: " << fuelLevel << "%" << endl;
    }

    void wheelie() {
        cout << brand << " " << model << " делает вилли!" << endl;
    }
};

int main() {

    // TODO: Создать массив указателей на Vehicle
    Vehicle* vehicles[4]; // массив типа Vehicle

    // Добавить объекты Car и Motorcycle
    vehicles[0] = new Car("Ford", "Cuga", 2024, 4, "avtomat");
    vehicles[1] = new Car("Tayota", "Rav", 2025, 2, "mechanika");
    vehicles[2] = new Motorcycle("Moto1", "Model1", 2000, true);
    vehicles[3]= new Motorcycle("Moto2", "Model2", 2001, false);

    vehicles[0]->displayInfo();   
    for (int i = 0; i < 2; ++i) { // потратим 30% бензина
        vehicles[0]->startEngine(); 
        vehicles[0]->stopEngine(); 
    }
    cout << "\nпосле поездки уровень бенза: " << vehicles[0]->getFuelLevel() << "% " << endl; // бензина меньше, чем 100%
    vehicles[0]->refuel(10.2); // поменялся уровень бензина

    vehicles[2]->displayInfo();   
    for (int i = 0; i < 3; ++i) { // потратим 45% бензина
        vehicles[2]->startEngine(); 
        vehicles[2]->stopEngine(); 
    }
    cout << "\nпосле поездки уровень бенза: " << vehicles[2]->getFuelLevel() << "% " << endl; // бензина меньше, чем 100%
    vehicles[2]->refuel(30.5); // поменялся уровень бензина

    // Продемонстрировать полиморфное поведение (указатель типа Vehicle работает с наследниками)
    cout << "-----------------------------" << endl;
    for (int i = 0; i < 4; ++i) {
        cout << "до старта бензина: " << vehicles[i]->getFuelLevel() << "%" << endl;
        vehicles[i]->startEngine();
        vehicles[i]->stopEngine();
        vehicles[i]->displayInfo();
        cout << "-----------------------------" << endl;
    }

    // vehicles[2]->wheelie(); // не работает, это указатель на Vehicle (у него нет метода wheelie)

    //а вот так будет работать
    Motorcycle* moto[2];
    moto[0] = new Motorcycle("Moto3", "Model3", 2003, true);
    moto[1]= new Motorcycle("Moto4", "Model4", 2004, false);
    moto[0]->wheelie();
    moto[1]->wheelie();

    // Очистка памяти
    for (int i = 0; i < 4; ++i) {
        delete vehicles[i];
    }

    return 0;
}
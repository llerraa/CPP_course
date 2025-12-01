#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Shape {
protected:
    string color;
    string name;

public:
    Shape(string n, string c) : name(n), color(c) {}
    virtual ~Shape() {}
    
    // TODO: Объявить чисто виртуальные методы:
    // - calculateArea()
    // - calculatePerimeter()
    // - draw()

    virtual double calculateArea() const = 0;

    virtual double calculatePerimeter() const = 0;

    virtual void draw() = 0;

    virtual void displayInfo() const {
        cout << "\nФигура: " << name << ", Цвет: " << color << endl;
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(string c, double r) : Shape("Круг", c), radius(r) {}
    
    // TODO: Реализовать виртуальные методы
    // Площадь круга: π * r²
    // Периметр круга: 2 * π * r

    double calculateArea() const override {
        cout << "*считаем площадь фигуры*" << endl;
        double S = 0;
        S = M_PI * pow(radius, 2);
        return S;
    }

    double calculatePerimeter() const override {
        cout << "*считаем периметр фигуры*" << endl;
        double P = 0;
        P = 2 * M_PI * radius;
        return P;
    }

    void draw() override {
        cout << "\nрисую фигуру " << name << " цветом " << color << endl;
        cout << "\nрадиуса " << radius << endl;
    }

    void displayInfo() const override {
        cout << "\nФигура: " << name << ", Цвет: " << color << endl;
        cout << "\nПлощадь: " << calculateArea() << ", \nПериметр: " << calculatePerimeter() << endl;
    }
};

class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(string c, double w, double h) : Shape("Прямоугольник", c), width(w), height(h) {}
    
    // TODO: Реализовать виртуальные методы

    double calculateArea() const override {
        cout << "*считаем площадь фигуры*" << endl;
        double S = width * height;
        return S;
    }

    double calculatePerimeter() const override {
        cout << "*считаем периметр фигуры*" << endl;
        double P = 2 * (width + height);
        return P;
    }

    void draw() override {
        cout << "\nрисую фигуру " << name << " цветом " << color << endl;
        cout << "\nпериметра " << calculatePerimeter() << endl;
    }

    void displayInfo() const override {
        cout << "\nФигура: " << name << ", Цвет: " << color << endl;
        cout << "\nПлощадь: " << calculateArea() << ", \nПериметр: " << calculatePerimeter() << endl;
    }
};

class Triangle : public Shape {
private:
    double sideA, sideB, sideC;

public:
    Triangle(string c, double a, double b, double s) : Shape("Треугольник", c), sideA(a), sideB(b), sideC(s) {}
    
    // TODO: Реализовать виртуальные методы
    // Площадь по формуле Герона 
    // p = (a + b + c) / 2
    // S = √(p × (p - a) × (p - b) × (p - c))
    
    double calculateArea() const override {
        cout << "*считаем площадь фигуры*" << endl;
        double p = (sideA + sideB + sideC) / 2;
        double S = sqrt(p*(p - sideA)*(p - sideB)*(p - sideC));
        return S;
    }

    double calculatePerimeter() const override {
        cout << "*считаем периметр фигуры*" << endl;
        double P = sideA + sideB + sideC;
        return P;
    }

    void draw() override {
        cout << "\nрисую фигуру " << name << " цветом " << color << endl;
        cout << "периметра " << calculatePerimeter() << endl;
    }

    void displayInfo() const override {
        cout << "\nФигура: " << name << ", Цвет: " << color << endl;
        cout << "Площадь: " << calculateArea() << ", \nПериметр: " << calculatePerimeter() << endl;
    }

};

int main() {
    vector<Shape*> shapes; // вектор указателей на БАЗОВЫЙ класс
    shapes.push_back(new Circle("Красный", 5.0)); // добавляем указатель на ПРОИЗВОДНЫЙ класс
    shapes.push_back(new Rectangle("Синий", 4.0, 6.0));
    shapes.push_back(new Triangle("Зеленый", 3.0, 4.0, 5.0));
    
    // TODO: Продемонстрировать полиморфизм - вывести информацию
    // о всех фигурах через указатель на базовый класс
    
    for (Shape* shape : shapes) {
        shape->displayInfo();
        cout << "------------------------------------" << endl;
        shape->draw();
        cout << "------------------------------------" << endl;
    }

    // Очистка памяти
    for (auto shape : shapes) {
        delete shape;
    }
    
    return 0;
}
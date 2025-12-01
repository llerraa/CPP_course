#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
using namespace std;

template<typename t>
class stack {
private:
    vector<t> elements;
    int capacity;

public:
    stack(int size = 10) : capacity(size) {}
    
    // TODO: Реализовать методы:
    // - void push(const T& element)
    // - T pop()
    // - T top() const
    // - bool isEmpty() const
    // - bool isFull() const
    // - int size() const
    
    void push(const t& element) {
        if (isfull()) {
            throw overflow_error("стек переполнен");
        }
        elements.push_back(element);
    }
    
    t pop() {
        if (isempty()) {
            throw underflow_error("стек пуст");
        }
        t value = elements.back();
        elements.pop_back();
        return value;
    }
    
    t top() const {
        if (isempty()) {
            throw underflow_error("стек пуст");
        }
        return elements.back();
    }
    
    bool isempty() const {
        return elements.empty();
    }
    
    bool isfull() const {
        return elements.size() >= capacity;
    }
    
    int size() const {
        return elements.size();
    }
    
    void display() const {
        cout << "стек [";
        for (int i = 0; i < elements.size(); i++) {
            cout << elements[i];
            if (i < elements.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
};

template<typename t>
class queue {
private:
    vector<t> elements;
    int capacity;

public:
    queue(int size = 10) : capacity(size) {}
    
    void enqueue(const t& element) {
        if (isfull()) {
            throw overflow_error("очередь переполнена");
        }
        elements.push_back(element);
    }
    
    t dequeue() {
        if (isempty()) {
            throw underflow_error("очередь пуста");
        }
        t value = elements.front();
        elements.erase(elements.begin());
        return value;
    }
    
    t front() const {
        if (isempty()) {
            throw underflow_error("очередь пуста");
        }
        return elements.front();
    }
    
    bool isempty() const {
        return elements.empty();
    }
    
    bool isfull() const {
        return elements.size() >= capacity;
    }
    
    int size() const {
        return elements.size();
    }
    
    void display() const {
        cout << "очередь [";
        for (int i = 0; i < elements.size(); i++) {
            cout << elements[i];
            if (i < elements.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
};

int main() {
    
    // тестирование stack с int
    cout << "\nстек с int: " << endl;
    stack<int> intstack(5);
    
    cout << "добавляем элементы в стек:" << endl;
    for (int i = 1; i <= 5; i++) {
        intstack.push(i * 10);
        cout << "добавлен: " << i * 10 << ", размер: " << intstack.size() << endl;
    }
    intstack.display();
    
    cout << "\nверхний элемент: " << intstack.top() << endl;
    
    cout << "\nизвлекаем элементы из стека:" << endl;
    while (!intstack.isempty()) {
        cout << "извлечен: " << intstack.pop() << ", размер: " << intstack.size() << endl;
    }
    
    // тестирование stack с double
    cout << "\nстек с double: " << endl;
    stack<double> doublestack(4);
    
    doublestack.push(3.14);
    doublestack.push(2.71);
    doublestack.push(1.41);
    doublestack.display();
    
    cout << "верхний элемент: " << doublestack.top() << endl;
    cout << "извлечен: " << doublestack.pop() << endl;
    doublestack.display();
    
    // тестирование stack с string
    cout << "\nстек с string: " << endl;
    stack<string> stringstack(3);
    
    stringstack.push("привет");
    stringstack.push("мир");
    stringstack.push("c++");
    stringstack.display();
    
    cout << "верхний элемент: " << stringstack.top() << endl;
    cout << "извлечен: " << stringstack.pop() << endl;
    stringstack.display();
    
    // тестирование queue с int
    cout << "\nочередь с int: " << endl;
    queue<int> intqueue(4);
    
    cout << "добавляем элементы в очередь:" << endl;
    for (int i = 1; i <= 4; i++) {
        intqueue.enqueue(i * 5);
        cout << "добавлен: " << i * 5 << ", размер: " << intqueue.size() << endl;
    }
    intqueue.display();
    
    cout << "\nпервый элемент: " << intqueue.front() << endl;
    
    cout << "\nизвлекаем элементы из очереди:" << endl;
    while (!intqueue.isempty()) {
        cout << "извлечен: " << intqueue.dequeue() << ", размер: " << intqueue.size() << endl;
    }
    
    // тестирование queue с double
    cout << "\nочередь с double:" << endl;
    queue<double> doublequeue(3);
    
    doublequeue.enqueue(1.5);
    doublequeue.enqueue(2.5);
    doublequeue.enqueue(3.5);
    doublequeue.display();
    
    cout << "первый элемент: " << doublequeue.front() << endl;
    cout << "извлечен: " << doublequeue.dequeue() << endl;
    doublequeue.display();
    
    // тестирование queue с string
    cout << "\nочередь с string:" << endl;
    queue<string> stringqueue(3);
    
    stringqueue.enqueue("первый");
    stringqueue.enqueue("второй");
    stringqueue.enqueue("третий");
    stringqueue.display();
    
    cout << "первый элемент: " << stringqueue.front() << endl;
    cout << "извлечен: " << stringqueue.dequeue() << endl;
    stringqueue.display();
    
    // тестирование обработки ошибок
    cout << "\nобработка ошибок:" << endl;
    stack<int> smallstack(2);
    
    try {
        smallstack.push(1);
        smallstack.push(2);
        smallstack.push(3); // должно вызвать исключение
    } catch (const overflow_error& e) {
        cout << "ошибка: " << e.what() << endl;
    }
    
    queue<int> emptyqueue;
    try {
        emptyqueue.dequeue(); // должно вызвать исключение
    } catch (const underflow_error& e) {
        cout << "ошибка: " << e.what() << endl;
    }
    
    return 0;
}
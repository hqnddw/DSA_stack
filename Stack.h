//
// Created by hqnddw on 2019/5/21.
//

#ifndef DSA_STACK_STACK_H
#define DSA_STACK_STACK_H

#include <iostream>

using namespace std;

template<typename T>
class Stack {
public:
    Stack(int size=10000);

    ~Stack();

    bool isEmpty() const;

    bool isFull() const;

    void clear();

    int getSize() { return Top; }

    T pop();

    void push(T const &e);

    T top();

    void traversal();

private:
    int size;
    T *elem;
    int Top;
};


template<typename T>
Stack<T>::Stack(int size) {
    elem = new T[size];
    this->size = size;
    Top = 0;
}

template<typename T>
Stack<T>::~Stack() {
    delete[]elem;
    elem = nullptr;
}

template<typename T>
bool Stack<T>::isFull() const {
    return Top == size;
}


template<typename T>
bool Stack<T>::isEmpty() const {
    return Top == 0;
}

template<typename T>
void Stack<T>::clear() {
    Top = 0;
}

template<typename T>
void Stack<T>::push(const T &e) {
    if (isFull())
        cout << "stack is full" << endl;
    else elem[Top++] = e;
}

template<typename T>
T Stack<T>::pop() {
    if (isEmpty())
        cout << "stack is empty" << endl;

    T e = elem[--Top];
    return e;


}

template<typename T>
T Stack<T>::top() {
    if (isEmpty())
        cout << "stack is empty" << endl;
    return elem[Top - 1];
}

template<typename T>
void Stack<T>::traversal() {
    while (!isEmpty()) {
        cout << pop() << " ";
    }
    cout << endl;

}

#endif //DSA_STACK_STACK_H

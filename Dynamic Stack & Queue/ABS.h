//
// Created by ed lang on 9/30/22.
//

#pragma once
#include <iostream>
using namespace std;

template <typename T>
class ABS{
    int _size; // size
    int _capacity; // capacity
    T* _stack; // dynamic stack
    float scale_factor = 2.0f;
    int resize;

public:
    // Constructors, Assignment Operators, Destructor
    ABS(); // Default constructor. Maximum capacity should be set to 1, and current size set to 0;
    ABS(int capacity, float scale); // Constructor for an ABS with the specified starting maximum capacity.
    ABS(const ABS &d); // Copy Constructor
    ABS &operator=(const ABS &d); // Assignment operator
    ~ABS(); // Destructor

    // Mutators
    void push(T data); // Add a new item to the top of the stack and resize if necessary.
    T pop(); // Remove the item at the top of the stack, resizes if necessary, and return the value removed. Throws a runtime_error if the stack is empty.
    T peek(); // Return the value of the item at the top of the stack, without removing it. Throws a runtime_error if the stack is empty.

    // Accessors
    unsigned int getSize(); // Returns the current number of items in the ABS.
    unsigned int getMaxCapacity(); // Returns the current max capacity of the ABS.
    T *getData(); // Returns the array representing the stack.
    unsigned int getTotalResize();
};

template <typename T>
ABS<T>::ABS(){ // Default constructor. Maximum capacity should be set to 1, and current size set to 0;
    _capacity = 1;
    _size = 0;
    _stack = new T[_capacity];
    resize = 0;
}

template <typename T>
ABS<T>::ABS(int capacity, float scale){ // Constructor for an ABS with the specified starting maximum capacity.
    _capacity = capacity;
    _size = 0;
    _stack = new T[_capacity];
    scale_factor = scale;
    resize = 0;
}

template<typename T>
ABS<T>::ABS(const ABS &d) { // Copy Constructor
    _capacity = d._capacity;
    _size = d._size;
    _stack = new T[_capacity];
    for (int i = 0; i < _size; i++)
        _stack[i] = d._stack[i];
}

template<typename T>
ABS<T> &ABS<T>::operator=(const ABS &d) { // Assignment operator
        delete[] _stack;
        _capacity = d._capacity;
        _size = d._size;
        _stack = new T[_capacity];
        for (int i = 0; i < _size; i++)
            _stack[i] = d._stack[i];
    return *this;
}

template<typename T>
ABS<T>::~ABS() { // Destructor
    delete[] _stack;
}

template<typename T>
void ABS<T>::push(T data) {
    // Add a new item to the top of the stack and resize if necessary.
    if (_size == _capacity){
        _capacity *= scale_factor;
        T* temp = new T[_capacity];
        for (int i = 0; i < _size; i++){
            temp[i] = _stack[i];
        }
        delete[] _stack;
        _stack = temp;
        resize++;
    }
    _stack[_size] = data;
    _size++;
}

template<typename T>
T ABS<T>::pop() { // Remove the item at the top of the stack, resizes if necessary, and return the value removed. Throws a runtime_error if the stack is empty.
    if (_size == 0)
        throw runtime_error("Error: stack empty");
    _size--;
    if (((float)_size / (float)_capacity) < (1 / scale_factor)) {
        _capacity /= scale_factor;
        resize++;
    }
    T item = _stack[_size];
    T* temp = new T[_capacity];
    for (int i = 0; i < _size; i++){
        temp[i] = _stack[i];
    }

    delete[] _stack;
    _stack = temp;
    return item;
}

template<typename T>
T ABS<T>::peek() { // Return the value of the item at the top of the stack, without removing it. Throws a runtime_error if the stack is empty.
    if (_size == 0)
        throw runtime_error("Error: stack empty");
    return _stack[_size-1];
}

// Accessors
template<typename T>
unsigned int ABS<T>::getSize() { // return size
    return _size;
}

template<typename T>
unsigned int ABS<T>::getMaxCapacity() { // return capacity
    return _capacity;
}

template<typename T>
T* ABS<T>::getData(){ // return the array representation the stack
    return _stack;
}

template<typename T>
unsigned int ABS<T>::getTotalResize() {
    return resize;
}






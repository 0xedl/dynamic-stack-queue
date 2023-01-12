

#pragma once
#include <iostream>
using namespace std;

template <typename T>
class ABQ{
    int size;
    int capacity;
    float scale_factor;
    int total_resizes;
    T* q;


public:
    // Constructors, Copy, Assign Destructor
    ABQ(); // Default constructor. Maximum capacity should be set to 1, and current size set to 0;
    ABQ(int capacity, float scale_factor); // Constructor for an ABQ with the specified starting maximum capacity.
    ABQ(const ABQ &d);  // Copy Constructor
    ABQ &operator=(const ABQ &d); // Assignment operator
    ~ABQ(); // Destructor

    // Mutators
    void enqueue(T data); // Add a new item to end of the queue and resizes if necessary.
    T dequeue(); // Remove the item at front of the queue, resizes if necessary, and return the value removed. Throws a runtime_error if the queue is empty
    T peek(); // Return the value of the item at the front of the queue, without removing it. Throws a runtime_error if the queue is empty.

    //Accessors
    unsigned int getSize(); // Returns the current number of items in the ABQ.
    unsigned int getMaxCapacity(); // Returns the current max capacity of the ABQ.
    T* getData(); // Returns the array representing the queue.
    unsigned int getTotalResizes(); // Returns the total number of times the ABS has been resized
};

//Constructors
template<typename T>
ABQ<T>::ABQ() {
    capacity = 1;
    size = 0;
    scale_factor = 2.0f;
    total_resizes = 0;
    q = new T[capacity];
}

template<typename T>
ABQ<T>::ABQ(int capacity, float scale_factor) {
    this->capacity = capacity;
    this->size = 0;
    this-> scale_factor = scale_factor;
    this->total_resizes = 0;
    q = new T[this->capacity];
}

template<typename T>
ABQ<T>::ABQ(const ABQ &d) {
    capacity = d.capacity;
    size = d.size;
    q = new T[capacity];
    for (int i = 0; i < size; i++)
        q[i] = d.q[i];
}

template<typename T>
ABQ<T> &ABQ<T>::operator=(const ABQ &d) {
    delete[] q;
    capacity = d.capacity;
    size = d.size;
    q = new T[capacity];
    for (int i = 0; i < size; i++)
        q[i] = d.q[i];
    return *this;
}

template<typename T>
ABQ<T>::~ABQ() {
    delete[] q;
}

// Mutators
template<typename T>
void ABQ<T>::enqueue(T data) { // Add a new item to end of the queue and resizes if necessary.
    if (size == capacity){
        capacity *= scale_factor;
        T* temp = new T[capacity];
        for (int i = 0; i < size; i++){
            temp[i] = q[i];
        }
        delete[] q;
        q = temp;
        total_resizes++;
    }
    q[size] = data;
    size++;
}

template<typename T>
T ABQ<T>::dequeue() { // Remove the item at front of the queue, resizes if necessary, and return the value removed. Throws a runtime_error if the queue is empty
    if (size == 0)
        throw runtime_error("Nothing in queue");
    T item = q[0];
    size--;
    if ((capacity > 1) && ((float)size / (float)capacity) < (1 / scale_factor)) {
        capacity /= scale_factor;
        T* temp = new T[capacity];
        for (int i = 0; i < size; i++)
            temp[i] = q[i];
        delete[] q;
        q = temp;
        total_resizes++;
    }
    for (int i = 0; i < size; i++)
        q[i] = q[i+1];
    return item;
}

template<typename T>
T ABQ<T>::peek() {
    if (size == 0)
        throw runtime_error("Nothing in queue");
    return q[0];
}

// Accessors
template<typename T>
unsigned int ABQ<T>::getSize() {
    return size;
}

template<typename T>
unsigned int ABQ<T>::getMaxCapacity() {
    return capacity;
}

template<typename T>
T* ABQ<T>::getData(){
    return q;
}

template<typename T>
unsigned int ABQ<T>::getTotalResizes() {
    return total_resizes;
}




#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// Name: Chua Ze Ming
// ID: S10177361C
// Group: 02
// Class: P07

template <typename T>
class Vector
{
    // Attributes
   private:
    T* _elements = nullptr;
    uint32_t _size = 0;
    uint32_t _capacity = 0;

    // Private methods
   private:
    bool outOfRange(uint32_t index);
    void shrink(uint32_t capacity);
    void expand(uint32_t capacity);

    // Public methods
   public:
    // Constructors
    Vector();
    Vector(uint32_t size, T fill = T());
    Vector(const Vector<T>& other);

    // Destructors
    ~Vector();

    // add element to the end of the vector
    void pushBack(T element);

    // remove element given index
    void remove(uint32_t index);

    // remove last element
    void pop();

    // reserve capacity
    void reserve(uint32_t size);

    // get first element
    T& front();

    // get last element
    T& back();

    // returns true if it is empty and false if not
    bool isEmpty();

    // get size
    uint32_t size();

    // get capacity
    uint32_t capacity();

    // O(1) index accessors
    T& at(uint32_t index);
    T& operator[](uint32_t index);

    // Copy assignment operators
    Vector<T>& operator=(Vector<T>& other);
};

#include "vector.cpp"

#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

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

    void pushBack(T element);
    void remove(uint32_t index);
    void pop();
    void reserve(uint32_t size);

    T& front();
    T& back();

    bool isEmpty();

    uint32_t size();
    uint32_t capacity();

    // O(1) random accessors
    T& at(uint32_t index);
    T& operator[](uint32_t index);

    // Copy assignment operators
    Vector<T>& operator=(Vector<T>& other);
};

#include "vector.cpp"

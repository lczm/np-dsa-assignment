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

    // Destructors
    ~Vector();

    void pushBack(T element);
    void remove(uint32_t index);
    void reserve(uint32_t size);

    // Inserts before the index
    void insert(uint32_t index);
    bool isEmpty();

    uint32_t size();
    uint32_t capacity();

    // O(1) random accessors
    T& at(uint32_t);
    T& operator[](uint32_t index);
};

#include "vector.cpp"

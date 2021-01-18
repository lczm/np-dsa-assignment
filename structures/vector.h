#pragma once

template <typename T>
class Vector
{
   private:
    T* elements = nullptr;

   public:
    // Constructors
    Vector();
    Vector(uint32_t size, T fill);

    // Destructors
    ~Vector();

    void push_back(T element);
    void reserve(uint32_t size);

    // Inserts before the index
    void insert(uint32_t index);
    bool is_empty();

    uint32_t size();
    uint32_t capacity();

    // O(1) random accessors
    T& at(uint32_t);
    T& operator[](uint32_t index);
};

#include "vector.cpp"
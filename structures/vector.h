#pragma once

template <typename T>
class Vector
{
   private:
   public:
    Vector();
    ~Vector();

    void push_back(T element);
    void reserve(uint32_t size);

    // Inserts before the index
    void insert(uint32_t index);
    bool is_empty();

    T& operator[](uint32_t index);
};

#include "vector.cpp"
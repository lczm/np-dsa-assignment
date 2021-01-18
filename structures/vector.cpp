#include "vector.h"

template <typename T>
Vector<T>::Vector()
{
}

template <typename T>
Vector<T>::Vector(uint32_t size, T fill)
{
    // Point elements to the array created. This is fine
    // because the default is a nullptr.
    _elements = new T[size];
    for (size_t i = 0; i < size; i++)
    {
        _elements[i] = fill;
    }

    // Update size
    _size = size;
}

template <typename T>
Vector<T>::~Vector()
{
    if (_elements != nullptr)
    {
        delete[] _elements;
    }
}

template <typename T>
void Vector<T>::push_back(T element)
{
}

template <typename T>
void Vector<T>::reserve(uint32_t size)
{
}

template <typename T>
void Vector<T>::insert(uint32_t index)
{
}

template <typename T>
bool Vector<T>::is_empty()
{
    if (_elements == nullptr)
    {
        return true;
    }
    return false;
}

template <typename T>
uint32_t Vector<T>::size()
{
    return _size;
}

template <typename T>
uint32_t Vector<T>::capacity()
{
    return _capacity;
}

template <typename T>
T& Vector<T>::at(uint32_t index)
{
    return _elements[index];
}

template <typename T>
T& Vector<T>::operator[](uint32_t index)
{
    return _elements[index];
}
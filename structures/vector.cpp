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

// Private methods
template <typename T>
void Vector<T>::shrink(uint32_t size)
{
}

template <typename T>
void Vector<T>::expand(uint32_t capacity)
{
    T* temp = _elements;
    _elements = new T[capacity];
    for (uint32_t i = 0; i < _size; i++)
    {
        _elements[i] = temp[i];
    }

    if (temp != nullptr) delete[] temp;
}

template <typename T>
void Vector<T>::push_back(T element)
{
    if (_size == _capacity)
    {
        // Expand vector size by two
        if (_capacity == 0)
            _capacity = 1;
        else
            _capacity *= 2;

        expand(_capacity);
    }

    // Push back the element
    _elements[_size] = element;
    // Update the size
    _size++;
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
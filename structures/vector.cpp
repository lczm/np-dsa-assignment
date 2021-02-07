#ifndef _VECTOR_
#define _VECTOR_

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
Vector<T>::Vector(const Vector<T>& other)
{
    this->_elements = new T[other._size];
    for (uint32_t i = 0; i < other._size; i++)
    {
        this->_elements[i] = other._elements[i];
    }
    this->_size = other._size;
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
bool Vector<T>::outOfRange(uint32_t index)
{
    if (index < 0 || index >= _size)
    {
        return true;
    }
    return false;
}

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
void Vector<T>::pushBack(T element)
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
void Vector<T>::remove(uint32_t index)
{
    // Out of range
    if (outOfRange(index))
    {
        string errorMessage =
            "Index is out of range, Index : " + to_string(index) + " Size : " + to_string(_size);
        throw out_of_range(errorMessage.c_str());
    }

    // Delete the element at the index
    for (uint32_t i = index; i < _size - 1; i++)
    {
        _elements[i] = _elements[i + 1];
    }
    _size--;
}

template <typename T>
void Vector<T>::pop()
{
    if (_size < 1)
    {
        string errorMessage = "Attempting to pop an empty vector.";
        throw out_of_range(errorMessage.c_str());
    }
    remove(_size - 1);
}

template <typename T>
void Vector<T>::reserve(uint32_t size)
{
    expand(size);
}

template <typename T>
T& Vector<T>::front()
{
    if (_size < 1)
    {
        string errorMessage = "Attempting to get the front of an empty vector.";
        throw out_of_range(errorMessage.c_str());
    }
    return _elements[0];
}

template <typename T>
T& Vector<T>::back()
{
    if (_size < 1)
    {
        string errorMessage = "Attempting to get the back of an empty vector.";
        throw out_of_range(errorMessage.c_str());
    }
    return _elements[_size - 1];
}

template <typename T>
bool Vector<T>::isEmpty()
{
    if (_elements == nullptr || _size == 0)
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
    if (outOfRange(index))
    {
        string errorMessage =
            "Index is out of range, Index : " + to_string(index) + " Size : " + to_string(_size);
        throw out_of_range(errorMessage.c_str());
    }
    return _elements[index];
}

template <typename T>
T& Vector<T>::operator[](uint32_t index)
{
    if (outOfRange(index))
    {
        string errorMessage =
            "Index is out of range, Index : " + to_string(index) + " Size : " + to_string(_size);
        throw out_of_range(errorMessage.c_str());
    }
    return _elements[index];
}

// Copy assignment operator
template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>& other)
{
    if (this->capacity() < other.capacity())
    {
        delete[] this->_elements;

        this->_elements = new T[other.capacity()];
        // this->expand(other.capacity());
    }

    for (uint32_t i = 0; i < other.size(); i++)
    {
        this->_elements[i] = other[i];
    }

    this->_size = other.size();
    this->_capacity = other.capacity();
    return *this;
}

#endif
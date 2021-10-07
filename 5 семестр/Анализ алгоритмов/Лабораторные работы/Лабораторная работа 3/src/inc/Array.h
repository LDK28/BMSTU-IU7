#ifndef SRC_ARRAY_H
#define SRC_ARRAY_H

#include <iostream>
#include <memory>
#include <stdlib.h>

template <typename Type>
class Array {
public:
    Array(size_t length, Type filler);
    Array(Array &array);
    Array(Array &&array);
    ~Array() = default;

    Type &operator[](size_t i);

    Array<Type> &operator=(Array &array);
    Array<Type> &operator=(Array &&array);

    size_t getLength();
    void bubble(int (*cmp)(Type, Type));
    void selection(int (*cmp)(Type, Type));
    void qsort(int (*cmp)(Type, Type));
protected:
    std::shared_ptr<Type[]>data;
    size_t length;
private:
    void _qsort(int (*cmp)(Type, Type), int left, int right);
};


template<typename Type>
Array<Type>::Array(size_t length, Type filler)
{
    this->length = length;
    this->data = std::shared_ptr<Type[]>(new Type[length]);
    for (size_t i = 0; i < length; i++)
        data[i] = filler;
}

template<typename Type>
Array<Type> &Array<Type>::operator=(Array &array)
{
    this->data = std::shared_ptr<Type[]>(new Type[array.length]);
    this->length = array.length;
    for (size_t i = 0; i < array.length; i++)
        this->data[i] = array[i];
}

template<typename Type>
Array<Type> &Array<Type>::operator=(Array &&array)
{
    this->length = array.length;
    this->data = array.data;
}

template<typename Type>
Array<Type>::Array(Array &array)
{
    this->data = std::shared_ptr<Type[]>(new Type[array.length]);
    this->length = array.length;
    for (size_t i = 0; i < array.length; i++)
        this->data[i] = array[i];
}

template<typename Type>
Array<Type>::Array(Array &&array)
{
    this->length = array.length;
    this->data = array.data;
}

template<typename Type>
Type &Array<Type>::operator[](size_t i)
{
    return data[i];
}

template <typename Type>
size_t Array<Type>::getLength()
{
    return length;
}

template <typename Type>
std::ostream& operator<<(std::ostream& os, Array<Type>& arr)
{
    for (size_t i = 0; i < arr.getLength(); i++) {
        if (i != arr.getLength() - 1)
            std::cout << arr[i] << ", ";
        else
            std::cout << arr[i];
    }
    return os;
}

template <typename Type>
void Array<Type>::bubble(int (*cmp)(Type, Type))
{
    bool fl;
    for (size_t j = 1; j < length; j++) {
        fl = false;
        for (size_t i = 0; i < length - j; i++) {
            if (cmp(data[i], data[i + 1]) > 0) {
                Type tmp = data[i];
                data[i] = data[i + 1];
                data[i + 1] = tmp;
                fl = true;
            }
        }
        if (!fl)
            break;
    }
}

template <typename Type>
void Array<Type>::selection(int (*cmp)(Type, Type))
{
    for (size_t i = 0; i < length - 1; i++)
    {
        size_t min = i;
        for (size_t j = i + 1; j < length; j++)
        {
            if (cmp(data[j], data[min]) < 0)
            {
                min = j;
            }
        }
        if (min != i)
        {
            Type tmp = data[i];
            data[i] = data[min];
            data[min] = tmp;
        }
    }
}

template <typename Type>
void Array<Type>::qsort(int (*cmp)(Type, Type))
{
    _qsort(cmp, 0, int(length) - 1);
}

template <typename Type>
void Array<Type>::_qsort(int (*cmp)(Type, Type), int left, int right)
{
    Type middle = data[(right + left) / 2];

    int i = left;
    int j = right;

    while (i <= j)
    {
        while (cmp(data[i], middle) < 0)
            i++;
        while (cmp(data[j], middle) > 0)
            j--;

        if (i <= j)
        {
            Type tmp = data[i];
            data[i] = data[j];
            data[j] = tmp;
            i++;
            j--;
        }
    }
    if (left < j)
        _qsort(cmp, left, j);
    if (i < right)
        _qsort(cmp, i, right);
}
#endif //SRC_ARRAY_H

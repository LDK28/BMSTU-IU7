#ifndef CONSTITER_H
#define CONSTITER_H

#include "BaseIter.h"
#include "Iterator.h"

template<class Type>
class Vector;

template<typename Type>
class ConstIterator : public BaseIter
{
public:
    explicit ConstIterator(const ConstIterator<Type>& iter);
    explicit ConstIterator(const Vector<Type>& vec);

    const Type& operator*() const;
    const Type* operator->() const;
    operator bool() const;

    ConstIterator<Type>& operator=(const Iterator<Type>& iter);

    ConstIterator<Type>& operator+=(int n);
    ConstIterator<Type> operator+(int n) const;
    ConstIterator<Type>& operator++();
    ConstIterator<Type> operator++(int);

    ConstIterator<Type>& operator-=(int n);
    ConstIterator<Type> operator-(int n) const;
    ConstIterator<Type>& operator--();
    ConstIterator<Type> operator--(int);

    bool operator<=(const ConstIterator<Type>& b) const;
    bool operator<(const ConstIterator<Type>& b) const;
    bool operator>=(const ConstIterator<Type>& b) const;
    bool operator>(const ConstIterator<Type>& b) const;
    bool operator==(const ConstIterator<Type>& b) const;
    bool operator!=(const ConstIterator<Type>& b) const;

    bool check(int line) const;

private:
    std::weak_ptr<Type> ptr;

protected:
    Type* get_cur_ptr() const;
};

template<class Type>
Type* ConstIterator<Type>::get_cur_ptr() const
{
    std::shared_ptr<Type> copy_ptr = ptr.lock();
    return copy_ptr.get() + index;
}

template<class Type>
ConstIterator<Type>::ConstIterator(const Vector<Type>& vec)
{
    index = 0;
    num_elem = vec.num_elem;
    ptr = vec.data_list;
    index = 0;
}

template<class Type>
ConstIterator<Type>::ConstIterator(const ConstIterator<Type>& iter)
{
    ptr = iter.ptr;
    index = iter.index;
    num_elem = iter.num_elem;
}

template<class Type>
const Type& ConstIterator<Type>::operator*() const
{
    check(__LINE__);

    std::shared_ptr<Type> copy_ptr = ptr.lock();
    return *get_cur_ptr();
}

template<class Type>
const Type* ConstIterator<Type>::operator->() const
{
    check(__LINE__);

    return get_cur_ptr();
}

template<class Type>
ConstIterator<Type>& ConstIterator<Type>::operator=(const Iterator<Type>& iter)
{
    check(__LINE__);

    ptr = iter.ptr;
    return *this;
}

template<class Type>
ConstIterator<Type>& ConstIterator<Type>::operator+=(int n)
{
    check(__LINE__);
    ptr += n;

    return *this;
}

template<class Type>
ConstIterator<Type> ConstIterator<Type>::operator+(int n) const
{
    check(__LINE__);
    ConstIterator<Type> iter(*this);
    iter += n;

    return iter;
}

template<class Type>
ConstIterator<Type> ConstIterator<Type>::operator++(int)
{
    check(__LINE__);
    ++(*this);

    return *this;
}

template<class Type>
ConstIterator<Type>& ConstIterator<Type>::operator++()
{
    check(__LINE__);
    ++index;

    return *this;
}

template<class Type>
ConstIterator<Type>& ConstIterator<Type>::operator-=(int n)
{
    check(__LINE__);
    index -= n;

    return *this;
}

template<class Type>
ConstIterator<Type> ConstIterator<Type>::operator-(int n) const
{
    check(__LINE__);

    ConstIterator<Type> iter(*this);
    iter -= n;

    return iter;
}

template<class Type>
ConstIterator<Type> ConstIterator<Type>::operator--(int)
{
    check(__LINE__);
    --(*this);

    return *this;
}

template<class Type>
ConstIterator<Type>& ConstIterator<Type>::operator--()
{
    check(__LINE__);
    --index;

    return *this;
}

template<class Type>
bool ConstIterator<Type>::operator<=(const ConstIterator<Type>& b) const
{
    check(__LINE__);

    return ptr <= b.ptr;
}

template<class Type>
bool ConstIterator<Type>::operator<(const ConstIterator<Type>& b) const
{
    check(__LINE__);

    return ptr < b.ptr;
}

template<class Type>
bool ConstIterator<Type>::operator>=(const ConstIterator<Type>& b) const
{
    check(__LINE__);

    return ptr >= b.ptr;
}

template<class Type>
bool ConstIterator<Type>::operator>(const ConstIterator<Type>& b) const
{
    check(__LINE__);

    return ptr > b.ptr;
}

template<class Type>
bool ConstIterator<Type>::operator==(const ConstIterator<Type>& b) const
{
    check(__LINE__);

    return ptr == b.ptr;
}

template<class Type>
bool ConstIterator<Type>::operator!=(const ConstIterator<Type>& b) const
{
    check(__LINE__);

    return ptr != b.ptr;
}

template<class Type>
ConstIterator<Type>::operator bool() const
{
    check(__LINE__);

    if (index >= num_elem || index < 0 || (num_elem == 0))
        return false;
    else
        return true;
}

template<class Type>
bool ConstIterator<Type>::check(int line) const
{
    if (!ptr.expired())
        return true;

    time_t t_time = time(NULL);
    throw deletedObj(__FILE__, typeid(*this).name(), line, ctime(&t_time));
    return false;
}

#endif // CONSTITER_H

#ifndef class_Vector_h
#define class_Vector_h

#include <stdarg.h>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <stdexcept>

#include "BaseVector.h"
#include "Iterator.h"
#include "ConstIterator.h"

#define EPS 1e-5

template<typename Type>
class Vector: public BaseVector
{
public:
    friend class Iterator<Type>;
    
    Vector();
    explicit Vector(int num_elements);
    Vector(int num_elements, Type* vec);
    Vector(int num_elements, Type vec, ...);
    Vector(std::initializer_list<Type> args);
    explicit Vector(const Vector<Type> &vec);
    Vector(Vector<Type>&& vec) noexcept;

    ~Vector();
    
    Vector<Type>& operator =(const Vector<Type>& vec);
    Vector<Type>& operator =(Vector<Type> &&vec);
    Vector<Type>& operator =(std::initializer_list<Type> args);

    bool is_zero() const;
    bool is_single() const;

    int size() const;
    Type len() const;

    Type& operator [](int index);
    const Type& operator [](int index) const;

    Type& get_elem_Vector(int index);
    const Type& get_elem_Vector(int index) const;
    bool set_elem_Vector(int index, const Type& vec);
    
    Vector<Type> get_single_vector() const;
    Vector<Type>& operator *=(const Type& mult);
    Vector<Type>& operator /=(const Type& div);
    Vector<Type> operator -();
    
    Type operator *(const Vector<Type>& vec) const;
    Vector<Type>& operator &=(const Vector<Type>& vec);
    Vector<Type> operator &(const Vector<Type>& vec) const;
    Vector<Type> operator +(const Vector<Type>&) const;
    Vector<Type>& operator +=(const Vector<Type>&);
    Vector<Type> operator -(const Vector<Type>&) const;
    Vector<Type>& operator -=(const Vector<Type>&);

    // Analogs of operators in methods
    Vector<Type>& add(const Vector<Type>&);                         // Vector<Type>& operator +=(const Vector<Type>&);
    Vector<Type>& subtract(const Vector<Type>&);                    // Vector<Type>& operator -=(const Vector<Type>&);
    Vector<Type>& vector_multiplication(const Vector<Type>& vec);   // Vector<Type>& operator &=(const Vector<Type>& vec);
    Type scalar_multiplication(const Vector<Type>& vec) const;      // Type operator *(const Vector<Type>& vec) const;
    
    double angle_between_vectors(const Vector<Type>&) const;
    bool is_collinearity(const Vector<Type>&) const;
    bool is_orthogonality(const Vector<Type>&) const;

    bool operator ==(const Vector<Type>&) const;
    bool operator !=(const Vector<Type>&) const;

    Iterator<Type> begin();
    Iterator<Type> end();

    Iterator<Type> begin() const;
    Iterator<Type> end() const;

    ConstIterator<Type> c_begin();
    ConstIterator<Type> c_end();
    
private:
    std::shared_ptr<Type> data_list;

protected:
    Type sum_all_elem();
    void sum_vectors(Vector<Type> &result, const Vector<Type>& vec1, const Vector<Type>& vec2) const;
    void difference_vectors(Vector<Type> &result, const Vector<Type>& vec1, const Vector<Type>& vec2) const;
    void mult_vectors(Vector<Type> &result, const Vector<Type>& vec1, const Vector<Type>& vec2) const;
    void new_dyn_mem(int);
};

template<typename Type>
std::ostream& operator <<(std::ostream& os, const Vector<Type>& vec)
{
    Iterator<Type> iter(vec);
    
    if (!iter)
    {
        os << "Vector is empty.";
        return os;
    }
    
    os << '(' << *iter;
    for (iter++; iter; iter++)
        os << ", " << *iter ;
    os << ')';
    
    return os;
}

#endif 

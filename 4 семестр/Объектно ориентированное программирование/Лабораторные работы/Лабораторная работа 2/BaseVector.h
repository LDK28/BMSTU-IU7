#ifndef BaseVector_h
#define BaseVector_h

#include <time.h>

template<typename Type>
class Iterator;

class BaseVector {
public:
    BaseVector();
    BaseVector(const BaseVector&);
    ~BaseVector();
    
    bool is_empty() const;
    int get_size() const;
    
protected:
    int num_elem = 0;
};

#endif /* BaseVector_h */

#ifndef BaseIter_h
#define BaseIter_h

class BaseIter
{
public:
    BaseIter();
    BaseIter(const BaseIter&);
    ~BaseIter();
    
protected:
    int index = 0;
    int num_elem = 0;
};

#endif /* BaseIter_h */

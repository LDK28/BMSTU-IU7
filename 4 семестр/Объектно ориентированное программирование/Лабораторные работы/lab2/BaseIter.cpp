#include "BaseIter.h"

BaseIter::BaseIter()
{
    index = 0;
    num_elem = 0;
}

BaseIter::BaseIter(const BaseIter& iter)
{
    index = iter.index;
    num_elem = iter.num_elem;
}

BaseIter::~BaseIter()
{

}

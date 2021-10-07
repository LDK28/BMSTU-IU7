#include <iostream>
#include "Array.h"
#include <sys/time.h>

using namespace std;



typedef struct
{
    int f, s;
}at;


int cmp(int a, int b)
{
    return a - b;
}


std::ostream& operator<<(std::ostream& os, at elem)
{
    std::cout << "{ " << elem.f << ", " << elem.s << "} ";
    return os;
}


template <typename Type>
double checkTime(Array<Type> &a, int (*cmp)(Type, Type), void (Array<Type>::*sort)(int (*cmp)(Type, Type)))
{
    struct timeval tv_start, tv_stop;
    double time = 0;
    for (int i = 0; i < 100; i++) {
        for (size_t i = 0; i < a.getLength(); i++)
            // a[i] = i;
            //a[i] = a.getLength() - i; 
            a[i] = rand() % 1000 - 500;
        gettimeofday(&tv_start, NULL);
        (a.*sort)(cmp);
        gettimeofday(&tv_stop, NULL);
        time += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    }
    time /= 100.0;
    return time;
}


int main()
{
    for (int size = 10; size < 1000; size += 100)
    {
        printf("%d &", size);
        Array<int> a(size, 1);
        printf(" %.2lf &", checkTime(a, cmp, &Array<int>::bubble));
        printf(" %.2lf &", checkTime(a, cmp, &Array<int>::selection));
        printf(" %.2lf  \\\\ \n\\hline", checkTime(a, cmp, &Array<int>::qsort));
        printf("\n");
    }

    return 0;
}

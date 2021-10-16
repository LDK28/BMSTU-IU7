#include "time_compare.hpp"
#include "levenstein.hpp"
#include "getCPUTime.hpp"
#include "string_gen.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

void time_compare()
{
    double start;
    double end;
    cout << setw(37) << "Time in ms" << endl;
    cout << setw(4) << "Len" << setw(15) << "Matrix" << setw(15) << "Recursion" << setw(15) << "With cache" << setw(15) << "Domerau" << endl;
    size_t n = 100000;
    for (size_t j = 5; j < 10; j += 1)
    {
        string str1 = string_gen(j), str2 = string_gen(j);
        cout << setw(4) << j;
        start = getCPUTime();
        for (size_t i = 0; i < n; i++)
            matr_method(str1, str2);
        end = getCPUTime();
        cout << setw(15) << (end - start) / n;

        start = getCPUTime();
        for (size_t i = 0; i < n / 100; i++)
            recur_method(str1, str2);
        end = getCPUTime();
        cout << setw(15) << (end - start) / n * 100;

        start = getCPUTime();
        for (size_t i = 0; i < n; i++)
            rec_cache_method(str1, str2);
        end = getCPUTime();
        cout << setw(15) << (end - start) / n;

        start = getCPUTime();
        for (size_t i = 0; i < n; i++)
            Domerau_method(str1, str2);
        end = getCPUTime();
        cout << setw(15) << (end - start) / n << endl;
    }

    n = 10000;
    for (size_t j = 10; j < 60; j += 10)
    {
        string str1 = string_gen(j), str2 = string_gen(j);
        cout << setw(4) << j;
        start = getCPUTime();
        for (size_t i = 0; i < n; i++)
            matr_method(str1, str2);
        end = getCPUTime();
        cout << setw(15) << (end - start) / n;

        cout << setw(15) << "";

        start = getCPUTime();
        for (size_t i = 0; i < n; i++)
            rec_cache_method(str1, str2);
        end = getCPUTime();
        cout << setw(15) << (end - start) / n;

        start = getCPUTime();
        for (size_t i = 0; i < n; i++)
            Domerau_method(str1, str2);
        end = getCPUTime();
        cout << setw(15) << (end - start) / n << endl;
    }
}

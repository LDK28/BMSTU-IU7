#include <iostream>
#include "Matrix.h"

double checkTime(Matrix &a, Matrix &b, Matrix (Matrix::*mul)(Matrix &matr, clock_t &time))
{
    double time = 0;
    clock_t t;
    for (int i = 0; i < 10; i++) {
        (a.*mul)(b, t);
        time += t;
    }
    time /= 10;
    time /= 0.001 * CLOCKS_PER_SEC;
    return time;
}

std::ostream& operator<<(std::ostream& os, Matrix matr)
{
    size_t i = 0;
    for (size_t i = 0; i < matr.getRows(); ++i) {
        for (int j = 0; j < matr.getCols(); ++j) {
            std::cout << matr.getElem(i, j) << " ";
        }
        std::cout << std::endl;
    }
    return os;
}

int main() {
    // Example
    Matrix a = {{1, -2, 3},
                {1, 2, 3},
                {1,  2,  3}};
    Matrix b = {{-1, 2, 3},
                {1, 2, 3},
                {1,  2,  3}};

    clock_t t;
    std::cout << a.convMul(b, t);
    std::cout << a.vinogradMul(b, t);
    std::cout << a.optimizedMul(b, t);

        // latex
    for (int size = 1001; size < 2101; size += 100) {
        printf("%d &", size);
        Matrix a(100, size);
        Matrix b(size, 100);
        a.fillRand();
        b.fillRand();
        printf(" %.2lf &", checkTime(a, b, &Matrix::convMul));
        printf(" %.2lf &", checkTime(a, b, &Matrix::vinogradMul));
        printf(" %.2lf  \\\\ \n\\hline", checkTime(a, b, &Matrix::optimizedMul));
        printf("\n");
    }


    // int beg = 1001;
    // int end = 2101;
    // printf("x = [");
    // for (int size = beg; size < end; size += 100) {
    //     Matrix a(100, size); 
    //     Matrix b(size, 100);
    //     a.fillRand();
    //     b.fillRand();;
    //     if (size != end - 100)
    //         printf("%d, ", size);
    //     else
    //         printf("%d", size);
    // }
    // printf("]\n");

    // printf("ConventionalMul = [");
    // for (int size = beg; size < end; size += 100) {
    //     Matrix a(100, size); 
    //     Matrix b(size, 100);
    //     a.fillRand();
    //     b.fillRand();;
    //     if (size != end - 100)
    //         printf("%.2lf, ", checkTime(a, b, &Matrix::convMul));
    //     else
    //         printf("%.2lf",  checkTime(a, b, &Matrix::convMul));
    // }
    // printf("]\n");

    // printf("VinodradMul = [");
    // for (int size = beg; size <end; size += 100) {
    //     Matrix a(100, size); 
    //     Matrix b(size, 100);
    //     a.fillRand();
    //     b.fillRand();;
    //     if (size != end - 100)
    //         printf("%.2lf, ",  checkTime(a, b, &Matrix::vinogradMul));
    //     else
    //         printf("%.2lf", checkTime(a, b, &Matrix::vinogradMul));
    // }
    // printf("]\n");

    // printf("VinogradOptimized = [");
    // for (int size = beg; size <end; size += 100) {
    //     Matrix a(100, size); 
    //     Matrix b(size, 100);
    //     a.fillRand();
    //     b.fillRand();;
    //     if (size != end - 100)
    //         printf("%.2lf, ", checkTime(a, b, &Matrix::optimizedMul));
    //     else
    //         printf("%.2lf", checkTime(a, b, &Matrix::optimizedMul));
    // }
    // printf("]\n");
    return 0;
}

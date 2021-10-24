#ifndef SRC_MATRIX_H
#define SRC_MATRIX_H

#include <cstddef>
#include <initializer_list>
#include "MatrixError.h"
#include <cstdlib>
#include <time.h>
class Matrix
{
public:
    friend class Strategy;
    Matrix(size_t n, size_t m);
    ~Matrix();
    Matrix(Matrix &matrix);
    Matrix(Matrix &&matrix);

    Matrix &operator=(Matrix &matrix);
    Matrix &operator=(Matrix &&matrix);
    Matrix(std::initializer_list<std::initializer_list<double> > init_list);
    Matrix &operator=(std::initializer_list<std::initializer_list<double> > init_list);
    size_t getCols();
    size_t getRows();
    double getElem(size_t i, size_t j);

    Matrix convMul(Matrix &matr, clock_t&time);
    Matrix vinogradMul(Matrix &matr, clock_t&time);
    Matrix optimizedMul(Matrix &matr, clock_t&time);
    void fillRand();
private:
    double **matrix_ptr;
    size_t rows, cols;
    double **alloc_matrix(size_t rows, size_t cols);
    void free_matrix();
};

#endif //SRC_MATRIX_H

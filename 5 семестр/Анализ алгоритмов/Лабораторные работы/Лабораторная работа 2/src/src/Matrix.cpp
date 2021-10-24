#include "Matrix.h"

void Matrix::free_matrix()
{
    for (size_t i = 0; i < rows; i++) {
        free(matrix_ptr[i]);
    }
    free(matrix_ptr);
}

double ** Matrix::alloc_matrix(size_t rows, size_t cols)
{
    double **matrix_ptr = (double **)calloc(rows, sizeof(double *));
    if (matrix_ptr == NULL)
        throw Matrix_Exception(__FILE__, __LINE__, __TIME__, "Cant allocate memory");
    for (size_t i = 0; i < rows; i++) {
        matrix_ptr[i] = (double *) malloc(cols * sizeof(double ));
        if (matrix_ptr[i] == NULL) {
            free_matrix();
            throw Matrix_Exception(__FILE__, __LINE__, __TIME__, "Cant allocate memory");
        }
    }
    return matrix_ptr;
}

Matrix::Matrix(size_t rows, size_t columns)
{
    this->rows = rows;
    this->cols = columns;
    this->matrix_ptr = alloc_matrix(rows, columns);
}

Matrix::~Matrix()
{
    free_matrix();
}

Matrix::Matrix(Matrix &matrix)
{
    free_matrix();
    this->rows = matrix.rows;
    this->cols = matrix.cols;
    this->matrix_ptr = alloc_matrix(matrix.rows, matrix.cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            matrix_ptr[i][j] = matrix.matrix_ptr[i][j];
}

Matrix::Matrix(Matrix &&matrix)
{
    free_matrix();
    this->rows = matrix.rows;
    this->cols = matrix.cols;
    this->matrix_ptr = matrix.matrix_ptr;
}

Matrix &Matrix::operator=(Matrix &matrix)
{
    free_matrix();
    this->rows = matrix.rows;
    this->cols = matrix.cols;
    this->matrix_ptr = alloc_matrix(matrix.rows, matrix.cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            matrix_ptr[i][j] = matrix.matrix_ptr[i][j];
    return *this;
}

Matrix &Matrix::operator=(Matrix &&matrix)
{
    free_matrix();
    this->rows = matrix.rows;
    this->cols = matrix.cols;
    this->matrix_ptr = matrix.matrix_ptr;
    return *this;
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double> > init_list)
{
    size_t rows = init_list.size();
    auto it = init_list.begin();
    size_t cols = it->size();

    for (const auto &row_list: init_list)
        if (row_list.size() != cols)
        {
            throw Matrix_Exception(__FILE__, __LINE__, __TIME__, "wrong size of initializer row (must be equal)");
        }

    this->rows = rows;
    this->cols = cols;
    this->matrix_ptr = alloc_matrix(rows, cols);
    size_t i = 0;
    for (const auto &ilist: init_list)
        for (const auto &elem: ilist)
        {
            matrix_ptr[i / cols][i % cols] = elem;
            i++;
        }
}

Matrix &Matrix::operator=(std::initializer_list<std::initializer_list<double> > init_list)
{
    Matrix tmp = Matrix(init_list);
    *this = tmp;
    return *this;
}

size_t Matrix::getCols()
{
    return cols;
}

size_t Matrix::getRows()
{
    return rows;
}

Matrix Matrix::convMul(Matrix &matr, clock_t&time)
{
    Matrix result(rows, matr.cols);
    clock_t sTime = clock();
    for (size_t i = 0; i < rows; i++) {
        for (size_t k = 0; k < matr.cols; k++) {
            result.matrix_ptr[i][k] = 0;
            for (size_t j = 0; j < cols; j++)
                result.matrix_ptr[i][k] = result.matrix_ptr[i][k] + matrix_ptr[i][j] * matr.matrix_ptr[j][k];
        }
    }
    clock_t eTime = clock();
    time = eTime - sTime;
    return result;
}

double Matrix::getElem(size_t i, size_t j)
{
    return matrix_ptr[i][j];
}

Matrix Matrix::vinogradMul(Matrix &matr, clock_t&time)
{
    Matrix res(rows, matr.cols);
    double *rowFactor = (double *) malloc (rows * sizeof(double));
    double *colFactor = (double *) malloc (matr.cols * sizeof(double ));

    clock_t sTime = clock();
    int d = this->cols / 2;
    for (int i = 0; i < this->rows; i++) {
        rowFactor[i] = matrix_ptr[i][0] * matrix_ptr[i][1];
        for (int j = 1; j < d; j++)
            rowFactor[i] = rowFactor[i] + matrix_ptr[i][2 * j] * matrix_ptr[i][2 * j + 1];

    }

    for (int i = 0; i < matr.cols; i++) {
        colFactor[i] = matr.matrix_ptr[0][i] * matr.matrix_ptr[1][i];
        for (int j = 1; j < d; j++)
            colFactor[i] = colFactor[i] + matr.matrix_ptr[2 * j][i] * matr.matrix_ptr[2 * j + 1][i];
    }

    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < matr.cols; j++) {
            res.matrix_ptr[i][j] = -rowFactor[i] - colFactor[j];
            for (int k = 0; k < d; k++)
                res.matrix_ptr[i][j] = res.matrix_ptr[i][j] + (matrix_ptr[i][2 * k] + matr.matrix_ptr[2 * k + 1][j]) *
                                                              (matrix_ptr[i][2 * k + 1] + matr.matrix_ptr[2 * k][j]);
        }
    }

    if (this->cols % 2 == 1)
    {
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < matr.cols; j++)
                res.matrix_ptr[i][j] = res.matrix_ptr[i][j] + matrix_ptr[i][this->cols - 1] *
                                                              matr.matrix_ptr[this->cols - 1][j];
    }
    clock_t eTime = clock();
    time = eTime - sTime;
    free(rowFactor);
    free(colFactor);
    return res;
}

void Matrix::fillRand()
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix_ptr[i][j] = rand() % 1000 - 500;
}

Matrix Matrix::optimizedMul(Matrix &matr, clock_t&time)
{
    Matrix res(rows, matr.cols);
    double *rowFactor = (double *) malloc (rows * sizeof(double));
    double *colFactor = (double *) malloc (matr.cols * sizeof(double ));

    clock_t sTime = clock();
    int d = cols - cols % 2;
    for (int i = 0; i < this->rows; ++i, ++i) 
    {
        rowFactor[i] = 0;
        for (int j = 0; j < d; ++j, ++j)
            rowFactor[i] = rowFactor[i] + matrix_ptr[i][j] * matrix_ptr[i][j + 1];
    }

    for (int i = 0; i < matr.cols; i++)
    {
        colFactor[i] = 0;
        for (int j = 0; j < d; ++j, ++j)
            colFactor[i] = colFactor[i] + matr.matrix_ptr[j][i] * matr.matrix_ptr[j + 1][i];
    }

    bool flag = this->cols % 2 == 1;
    double buf;
    for (int i = 0; i < this->rows; ++i)
        for (int j = 0; j < matr.cols; ++j)
        {
            buf = -rowFactor[i] - colFactor[j];
            for (int k = 0; k < d; ++k, ++k)
                buf = buf + (matrix_ptr[i][k] + matr.matrix_ptr[k + 1][j]) *
                                                              (matrix_ptr[i][k + 1] + matr.matrix_ptr[k][j]);
            if (flag)
                buf = buf + matrix_ptr[i][this->cols - 1] * matr.matrix_ptr[this->cols - 1][j];
            res.matrix_ptr[i][j] = buf;
        }

    clock_t eTime = clock();
    time = eTime - sTime;
    free(rowFactor);
    free(colFactor);
    return res;
}
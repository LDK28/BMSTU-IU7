
#include "MatrixError.h"
Matrix_Exception::Matrix_Exception(const char* file, int line, const char* time, const char* msg)
{
    this->err_str = (char *)malloc(strlen(file) + strlen(time) + strlen(msg) + 40);
    sprintf(this->err_str, "file: %s, line: %-3d, time: %s, error: %s", file, line, time, msg);
}
Matrix_Exception::~Matrix_Exception()
{
    delete[] err_str;
}
const char * Matrix_Exception::what() const noexcept
{
    return this->err_str;
}
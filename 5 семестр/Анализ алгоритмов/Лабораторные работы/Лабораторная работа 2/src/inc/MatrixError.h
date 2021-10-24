#ifndef SRC_MATRIXERROR_H
#define SRC_MATRIXERROR_H


#include <exception>
#include <string>
#include <string.h>
class Matrix_Exception : public std::exception
{
public:
    Matrix_Exception(const char* file, int line, const char* time, const char* msg);

    virtual ~Matrix_Exception();

    virtual const char * what() const noexcept override;

protected:
    char * err_str;
};


#endif //SRC_MATRIXERROR_H

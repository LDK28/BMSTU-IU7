#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>
#include <cstring>

class base_exception : public std::exception
{
protected:
    std::string exception_info;
public:
    base_exception(std::string time, std::string filename, std::string classname, std::string methodname)
    {
        exception_info = "\n" + time + "\n" + filename +  "\n" + classname + "\n" + methodname;
    }

    virtual const char *what() const noexcept override = 0;
};

class memory_exception : public base_exception
{
public:
    memory_exception(std::string time, std::string filename, std::string classname, std::string methodname)
        : base_exception(time, filename, classname, methodname)
    {

    };

    virtual const char *what() const noexcept override
    {
        std::string message = "\n MEMORY ERROR" + exception_info;

        char *ret_message = new char[message.size() + 1];

        std::strcpy(ret_message, message.c_str());
        return ret_message;
    }
};

class args_exception : public base_exception
{
public:
    args_exception(std::string time, std::string filename, std::string classname, std::string methodname)
        : base_exception(time, filename, classname, methodname)
    {

    };

    virtual const char *what() const noexcept override
    {
        std::string message = "\n ARGUMENTS ERROR" + exception_info;

        char *ret_message = new char[message.size() + 1];

        std::strcpy(ret_message, message.c_str());
        return ret_message;
    }
};

class camera_exception : public base_exception
{
public:
    camera_exception(std::string time, std::string filename, std::string classname, std::string methodname)
        : base_exception(time, filename, classname, methodname)
    {

    };

    virtual const char *what() const noexcept override
    {
        std::string message = "\n CAMERA ERROR" + exception_info;

        char *ret_message = new char[message.size() + 1];

        std::strcpy(ret_message, message.c_str());
        return ret_message;
    }
};

class file_exception : public base_exception
{
public:
    file_exception(std::string time, std::string filename, std::string classname, std::string methodname)
        : base_exception(time, filename, classname, methodname)
    {

    };

    virtual const char *what() const noexcept override
    {
        std::string message = "\n FILE ERROR" + exception_info;

        char *ret_message = new char[message.size() + 1];

        std::strcpy(ret_message, message.c_str());
        return ret_message;
    }
};

class iterator_exception : public base_exception
{
public:
    iterator_exception(std::string time, std::string filename, std::string classname, std::string methodname)
        : base_exception(time, filename, classname, methodname)
    {

    };

    virtual const char *what() const noexcept override
    {
        std::string message = "\n ITERATOR ERROR" + exception_info;

        char *ret_message = new char[message.size() + 1];

        std::strcpy(ret_message, message.c_str());
        return ret_message;
    }
};

#endif // EXCEPTIONS_H

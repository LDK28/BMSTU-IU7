#include "mysnprintf.h"

char *int_to_string(int number)
{
    size_t size = 0;
    int neg = 0;
    char *string;

    if (number == 0)
    {
        string = malloc(2 * sizeof(char));
        *string = '0';
        *(string + 1) = 0;
        return string;
    }
    else if (number < 0)
        neg = 1;

    int tmp = number;
    while (tmp)
    {
        tmp /= 10;
        ++size;
    }


    string = malloc((neg + size + 1) * sizeof(char));

    size_t i;
    for (i = 0; number; ++i)
    {
        if (neg)
            *(string + i) = '0' - (number % 10);
        else
            *(string + i) = '0' + (number % 10);
        number /= 10;
    }
    *(string + i) = 0;

    for (i = 0; i < size / 2; ++i)
    {
        char tmp = *(string + i);
        *(string + i) = *(string + size - 1 - i);
        *(string + size - 1 - i) = tmp;
    }
    if (neg)
    {
        for (i = neg + size; i != 0; --i)
            *(string + i) = *(string + i - 1);
        *string = '-';
    }
    return string;
}

int my_snprintf(char *restrict buffer, size_t buf_size, const char *restrict format, ...)
{ 
    size_t i;
    size_t pos = 0;
    va_list args;

    va_start(args, format);
    if (format)
    {
        for (i = 0; *(format + i); ++i)
        {
            if (*(format + i) != '%')
            {
                if ((pos < buf_size - 1) && buffer && (buf_size > 0))
                    *(buffer + pos) = *(format + i);
                ++pos;
            }
            else
            {
                ++i;

                if (*(format + i) == 'c')
                {
                    if ((pos < buf_size - 1) && buffer && (buf_size > 0))
                        *(buffer + pos) = va_arg(args, int);
                    ++pos;
                }
                else if (*(format + i) == 'd' || *(format + i) == 'i')
                {
                    int number = va_arg(args, int);
                    char *tmp_string = int_to_string(number);
                    
                    for (size_t j = 0; *(tmp_string + j); ++j)
                    {
                        if ((pos < buf_size - 1) && buffer && (buf_size > 0))
                            *(buffer + pos) = *(tmp_string + j);
                        ++pos;
                    }
                    free(tmp_string);
                }
                else if (*(format + i) == 's')
                {
                    char *string = va_arg(args, char*);
                    if (string == NULL)
                        string = "(null)";
                    for (size_t j = 0; *(string + j); ++j)
                    {
                        if ((pos < buf_size - 1) && buffer && (buf_size > 0))
                            *(buffer + pos) = *(string + j);
                        ++pos;
                    }
                }
                else
                {
                    if (pos < buf_size - 1)
                        *(buffer + pos) = *(format + i);
                    ++pos;
                }
            }
        }
    }
    va_end(args);

    if (buffer && buf_size > 0)
    {
        if (pos < buf_size - 1)
            *(buffer + pos) = 0;
        else
            *(buffer + buf_size - 1) = 0;
    }

    return pos;
}

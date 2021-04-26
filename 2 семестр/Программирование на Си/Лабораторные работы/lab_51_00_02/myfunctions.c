#include "myfunctions.h"

long average(FILE *f, double *num)
{
    double average = 0;
    size_t count = 0;
    double fnum;
    double dif;

    if (fscanf(f, "%lf", &fnum) == 1)
    {
        average += fnum;
        ++count;
        while (fscanf(f, "%lf", &fnum) == 1)
        {
            average += fnum;
            ++count;
        }
    }
    else
        return INCORRECT_DATA_ERROR;
    
    average = average / count;
    fseek(f, 0, SEEK_SET);

    if (fscanf(f, "%lf", &fnum) == 1)
    {
        dif = fabs(average - fnum);
        *num = fnum;
        while (fscanf(f, "%lf", &fnum) == 1)
            if (fabs(average - fnum) < dif)
            {
                dif = fabs(average - fnum);
                *num = fnum;
            }
    }

    return EXIT_SUCCESS;
}
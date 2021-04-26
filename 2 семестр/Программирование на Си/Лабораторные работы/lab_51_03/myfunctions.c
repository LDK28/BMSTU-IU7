#include "myfunctions.h"

long file_size(FILE *f, size_t *size)
{
    long sz;
    if (fseek(f, 0L, SEEK_END))
        return 1;
    sz = ftell(f);
    if (sz < 0)
        return 1;
    *size = sz;
    return fseek(f, 0L, SEEK_SET);
}

long create_bin_file(const char *file_name)
{
    FILE *f_in;
    f_in = fopen(file_name, "r");
    if (f_in == NULL)
        return OPEN_FILE_ERROR;

    int num;
    if (fscanf(f_in, "%d", &num) == 1)
    {
        FILE *f_out;
        f_out = fopen("out.bin", "wb");
        if (f_out == NULL)
            return OPEN_FILE_ERROR;
        
        fwrite(&num, sizeof (int), 1, f_out);
        while (fscanf(f_in, "%d", &num) == 1)
            fwrite(&num, sizeof (int), 1, f_out);

        fclose(f_out);
        fclose(f_in);
        return EXIT_SUCCESS;
    }
    else
    {
        fclose(f_in);
        return INCORRECT_FILE_ERROR;
    }
}

long print_bin_file(const char *file_name)
{
    FILE *f;
    f = fopen(file_name, "rb");
    if (f == NULL)
        return OPEN_FILE_ERROR;
    
    size_t size;
    int num;
    long rc = 0;

    rc = file_size(f, &size);
    if ((size == 0) || (size % sizeof(int) != 0))
        return INCORRECT_FILE_ERROR;

    if (rc == 0)
    {
        for (size_t i = 0; !rc && i < size / sizeof (int); i++)
        {
            if (fread(&num, sizeof (int), 1, f) == 1)
                printf("%d ", num);
            else
                rc = 1;
        }
        fclose(f);
        return EXIT_SUCCESS;
    }
    else
    {
        fclose(f);
        return DETERMINE_FILE_SIZE_ERROR;
    }
}

long get_number_by_pos(const char *file_name, size_t pos, int *num)
{
    FILE *f;
    f = fopen(file_name, "rb");
    if (f == NULL)
        return OPEN_FILE_ERROR;

    if (fseek(f, (pos - 1) * sizeof (int), SEEK_SET))
    {
        fclose(f);
        return INCORRECT_POSITION_ERROR;
    }
    if (fread(num, sizeof (int), 1, f) == 1)
    {
        fclose(f);
        return EXIT_SUCCESS;
    }
    else
    {
        fclose(f);
        return INCORRECT_POSITION_ERROR;
    }
}

long put_number_by_pos(const char *file_name, size_t pos, int num)
{
    FILE *f;
    f = fopen(file_name, "rb+");
    if (f == NULL)
        return OPEN_FILE_ERROR;

    if (fseek(f, (pos - 1) * sizeof (int), SEEK_SET))
    {
        fclose(f);
        return INCORRECT_DATA_ERROR;
    }
    fwrite(&num, sizeof (int), 1, f);
    
    fclose(f);
    return EXIT_SUCCESS;
}

long sort_bin_file(const char *file_name)
{
    FILE *f;
    f = fopen(file_name, "rb");
    if (f == NULL)
        return OPEN_FILE_ERROR;
    
    size_t size;
    long rc = 0;

    rc = file_size(f, &size);
    fclose(f);
    if ((size == 0) || (size % sizeof(int) != 0))
        return INCORRECT_FILE_ERROR;

    if (rc == 0)
    {
        size_t len = size / sizeof (int);
        int num, min;
        size_t min_pos;

        for (size_t i = 1; i < len; ++i)
        {
            if (get_number_by_pos(file_name, i, &min))
                return EXIT_FAILURE;
            min_pos = i;
            for (size_t j = i + 1; j <= len; ++j)
            {
                if (get_number_by_pos(file_name, j, &num))
                    return EXIT_FAILURE;
                if (num < min)
                {
                    min = num;
                    min_pos = j;
                }
            }
            if (get_number_by_pos(file_name, i, &num))
                return EXIT_FAILURE;
            if (put_number_by_pos(file_name, i, min))
                return EXIT_FAILURE;
            if (put_number_by_pos(file_name, min_pos, num))
                return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }
    else
        return DETERMINE_FILE_SIZE_ERROR;
}
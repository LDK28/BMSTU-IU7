#include "../inc/static_lib.h"

long count(const char *file_name)
{
    FILE *f;
    f = fopen(file_name, "r");
    if (f == NULL)
        return OPEN_FILE_ERROR;
    long count = 0;
    int num;
    long rc = 0;

    rc = 0;

    for (size_t i = 0; !rc && !i; i = feof(f))
    {
        if (fscanf(f, "%d", &num) == 1)
            ++count;
        else
            rc = 1;
    }
    fclose(f);
    if (rc == 1 || count == 0)
        return INCORRECT_DATA_ERROR;
    return count;
}

void input_array(int *pa, int *pb, const char *file_name)
{
    FILE *f;
    f = fopen(file_name, "r");
    for (size_t i = 0; pa + i != pb; i++)
        fscanf(f, "%d", (pa + i));
    fclose(f);
}

int compare(const void *num1, const void *num2)
{
    return *(int *)num1 - *(int *)num2;
}

void mysort(void *first, size_t number, size_t size, int (*comparator)(const void *, const void *))
{
    char *current_pos = (char *)first + size;
    char *current = malloc(size);
    char *pos;
    for (size_t i = 1; i < number; ++i)
    {
        pos = current_pos;
        memcpy(current, current_pos, size);
        for (int j = i; (j > 0) && (comparator(pos - size, current) > 0); --j)
        {
            memcpy(pos, pos - size, size);
            pos -= size;
        }
        memcpy(pos, current, size);
        current_pos += size;
    }
    free(current);
}

long output_array(int *pa, int *pb, const char *file_name)
{
    if (pa == pb || pa == NULL || pb == NULL)
        return INCORRECT_DYNAMICS_ERROR;
    
    FILE *f;
    f = fopen(file_name, "w");
    if (f == NULL)
        return OPEN_FILE_ERROR;
    
    for (size_t i = 0; pa + i != pb; ++i)
        fprintf(f, "%d ", *(pa + i));
    
    fclose(f);
    return EXIT_SUCCESS;
}

int key(const int *pa_src, const int *pb_src, int *pa_dst, size_t max_size, size_t *cur_size)
{
    if (pa_src == NULL || pb_src == NULL)
        return INCORRECT_DYNAMICS_ERROR;
    if (pb_src - pa_src < 2)
        return INCORRECT_DATA_ERROR;

    size_t pos_min = 0, pos_max = 0;
    for (size_t i = 0; pa_src + i != pb_src; ++i)
    {
        if (*(pa_src + i) < *(pa_src + pos_min))
            pos_min = i;
        if (*(pa_src + i) > *(pa_src + pos_max))
            pos_max = i;
    }

    if (pos_min > pos_max)
    {
        size_t temp = pos_min;
        pos_min = pos_max;
        pos_max = temp;
    }

    if (pos_max - pos_min < 2)
        return INCORRECT_DATA_ERROR;

    size_t cur_pos = 0;
    for (size_t i = pos_min + 1; i < pos_max && cur_pos < max_size; ++i)
    {
        *(pa_dst + cur_pos) = *(pa_src + i);
        ++cur_pos;
    }
    *cur_size = cur_pos;
    return EXIT_SUCCESS;
}

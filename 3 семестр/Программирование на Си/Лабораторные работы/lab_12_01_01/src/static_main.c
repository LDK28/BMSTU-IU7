#include "../inc/static_lib.h"

int *allocate_array(size_t size)
{
    int *data = malloc(size * sizeof(int));
    if (!data)
        return data;
    for (size_t i = 0; i < size; ++i)
    {
        *(data + i) = 0;
    }
    return data;
}

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    if (argc > 4 || argc < 3)
        return INCORRECT_INPUT_ERROR;

    long size = count(*(argv + 1));
    if (size <= 0)
        return EXIT_FAILURE;
    
    int *pa = allocate_array(size);
    if (pa == NULL)
        return INCORRECT_DYNAMICS_ERROR;
    int *pb = pa + size;

    input_array(pa, pb, *(argv + 1));

    int *pa_dst = NULL, *pb_dst = NULL;
    size_t cur_size = 0;
    if (argc == 4)
    {
        if (!strcmp(*(argv + 3), "f"))
        {
            pa_dst = malloc((pb - pa) * sizeof(int));
            if (key(pa, pb, pa_dst, pb - pa, &cur_size))
            {
                free(pa);
                return EXIT_FAILURE;
            }
            else
            {
                free(pa);
                pb_dst = pa_dst + cur_size;
            }
        }
        else
        {
            free(pa);
            return INCORRECT_INPUT_ERROR;
        }
    }
    else
    {
        pa_dst = pa;
        pb_dst = pb;
    }

    mysort(pa_dst, pb_dst - pa_dst, sizeof(int), compare);

    if (output_array(pa_dst, pb_dst, *(argv + 2)))
    {
        free(pa_dst);
        return EXIT_FAILURE;
    }
    free(pa_dst);
    return EXIT_SUCCESS;
}

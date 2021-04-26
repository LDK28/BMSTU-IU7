#include "array.h"

int main(void)
{
    setbuf(stdout, NULL);
    size_t n;
    if (scanf("%zu", &n) != 1)
        return EXIT_FAILURE;
    double *data = NULL;
    data = malloc(n * sizeof(long));
    if (!data)
        return EXIT_FAILURE;

    double mean;

    if (input_array_mean(data, n, &mean))
    {
        free(data);
        return EXIT_FAILURE;
    }

    puts("Inputed array:");
    output_array(data, n);

    if (insert_mean(&data, &n, mean))
        return EXIT_FAILURE;
    
    puts("\nAnswer:");
    output_array(data, n);
    
    free(data);
    return EXIT_SUCCESS;
}

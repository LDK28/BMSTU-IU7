#include <stdio.h>
#include <stdlib.h>

void output(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    int i, n, sum = 0;
    printf("Input size of array: ");
    scanf("%d",&n);

    int *a = (int *)malloc(n * sizeof(int));

    printf("Input %d elements of array: ", n);

    for (i = 0; i < n; i++)
    {
    	scanf("%d", (a + i));
        sum += a[i];
    }

    printf("Sum of %d elements of array: %d\n", n, sum);

    free(a);

    return 0;
}

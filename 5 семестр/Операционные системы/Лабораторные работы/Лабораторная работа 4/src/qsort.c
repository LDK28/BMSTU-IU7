#include <stdio.h>
#include <stdlib.h>

int comparator(const int *num1, const int *num2)
{
    return *num1 - *num2;
}

void output(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main(void)
{
    int i, n;
    printf("Введитре размер массива: ");
    scanf("%d",&n);

    int *a = NULL;
    a = (int*)malloc(n * sizeof(int));

    printf("Введите %d элементов массива: ", n);

    for (i = 0; i < n; i++)
    	scanf("%d", (a + i));
    
    qsort(a, n, sizeof(int), (int (*)(const void *, const void *))comparator);

    printf("Отсортированный массив:\n");
        output(a,n);
    
    free(a);
    return 0;
}

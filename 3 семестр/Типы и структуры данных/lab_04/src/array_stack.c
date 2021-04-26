#include "array_stack.h"

void init_array(array_stack_t *array)
{
    array->ptr_start = array->array - 1;
    array->ptr_end = array->array + ARRAY_CAPACITY;
    array->cur_ptr_start = array->ptr_start;
    array->cur_ptr_end = array->ptr_end;
    for (double *ptr = array->ptr_start + 1; ptr != array->ptr_end; ++ptr)
        *ptr = 0;
}

void print_array_stack(array_stack_t array)
{
    system("clear");
    printf("\n%zu element(s) from the beginning:\n", array.cur_ptr_start - array.ptr_start);
    
    for (double *ptr = array.cur_ptr_start; ptr > array.ptr_start; --ptr)
        printf("Element: %10lf\n", *ptr);

    printf("\n%zu element(s) from the end:\n", array.ptr_end - array.cur_ptr_end);
    for (double *ptr = array.cur_ptr_end; ptr < array.ptr_end; ++ptr)
        printf("Element: %10lf\n", *ptr);
}

int add_array_item(array_stack_t *array)
{
    if (array->cur_ptr_start + 1 == array->cur_ptr_end)
    {
        puts("The stack is full.");
        return FULL_STACK_ERROR;
    }
    int choice = -1;
    system("clear");
    puts("  1) Add an item to the beginning stack");
    puts("  2) Add an item to the end stack");
    printf("Select action: ");
    get_choice(&choice, 1, 2);
    if ((choice == 1 && array->cur_ptr_start + 1 == array->ptr_end) || (choice == 2 && array->cur_ptr_end - 1 == array->ptr_start))
    {
        puts("The stack is full.");
        return FULL_STACK_ERROR;
    }
    printf("Enter a number: ");
    double tmp;
    if (scanf("%lf", &tmp) != 1)
    {
        puts("Invalid input.");
        return INCORRECT_INPUT_ERROR;
    }
    if (choice == 1)
    {
        array->cur_ptr_start += 1;
        *(array->cur_ptr_start) = tmp;
    }
    else if (choice == 2)
    {
        array->cur_ptr_end -= 1;
        *(array->cur_ptr_end) = tmp;
    }
    return EXIT_SUCCESS;
}

int get_array_item(array_stack_t *array)
{
    int choice = -1;
    system("clear");
    puts("  1) Get an item from the beginning stack");
    puts("  2) Get an item from the end stack");

    get_choice(&choice, 1, 2);
    if ((choice == 1 && array->cur_ptr_start == array->ptr_start) || (choice == 2 && array->cur_ptr_end == array->ptr_end))
    {
        puts("The stack is empty.");
        return FULL_STACK_ERROR;
    }

    if (choice == 1)
    {
        printf("Element: %10lf\n", *(array->cur_ptr_start));
        *(array->cur_ptr_start) = 0;
        array->cur_ptr_start -= 1;
    }
    else if (choice == 2)
    {
        printf("Element: %10lf\n", *(array->cur_ptr_end));
        *(array->cur_ptr_end) = 0;
        array->cur_ptr_end += 1;
    }

    return EXIT_SUCCESS;
}

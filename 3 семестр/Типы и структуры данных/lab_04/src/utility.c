#include "utility.h"

void print_menu(void)
{
    system("clear");
    
    puts("Menu\n\n");

    puts("===== Array (2 stacks)");
    puts("  1) Print stack");
    puts("  2) Add an item to the stack");
    puts("  3) Get an item from array");
    puts("===== List");
    puts("  4) Print stack");
    puts("  5) Add an item to the stack");
    puts("  6) Get an item from list");

    puts("\n  7) Analysis");

    puts("  0) Exit\n");
    printf("Select action: ");
}

void get_enter(void)
{
    puts("Press space to continue...\n");
    int ch = 0;

    do
    {
        ch = getc(stdin);
    } while ((char)ch != ' ');

    system("clear");
}

void get_choice(int *choice, int start, int stop)
{
    while (1)
        {
            if (scanf("%d", choice) != 1)
            {
                puts("Invalid input");
                printf("Try again: ");
            }
            else
                if (*choice < start || *choice > stop)
                {
                    puts("Invalid input");
                    printf("Try again: ");
                }
                else
                    break;
        }
}

// functions for time check
void push_array_item(array_stack_t *array)
{
    double tmp = 1;
    array->cur_ptr_start += 1;
    *(array->cur_ptr_start) = tmp;
}

void push_list_stack_t(list_stack_t *stack) {

    double tmp = 1;
    node_t *node = stack->free_nodes;
    if (node)
        stack->free_nodes = stack->free_nodes->next;
    else
        node = create_node(tmp);

    node->next = stack->list;
    stack->list = node;
}

int pop_array_item(array_stack_t *array)
{
    if (array->cur_ptr_start == array->ptr_start || array->cur_ptr_end == array->ptr_end)
        return FULL_STACK_ERROR;

    *(array->cur_ptr_start) = 0;
    array->cur_ptr_start -= 1;

    *(array->cur_ptr_end) = 0;
    array->cur_ptr_end -= 1;

    return EXIT_SUCCESS;
}

int pop_list_stack_t(list_stack_t *stack, double *element)
{
    if (!stack->list)
        return EXIT_FAILURE;

    node_t* node = stack->list;

    *element = node->value;

    stack->list = node->next;

    // free(node);
    node->next = stack->free_nodes;
    stack->free_nodes = node;

    return 0;
}

size_t size_array_stack(size_t capacity)
{
  return capacity * sizeof(double) + 4 * sizeof(double*);
}

size_t size_list_stack(size_t count)
{
  return count * sizeof(node_t) + sizeof(list_stack_t);
}

int compare_methods()
{
    size_t counts = 100;

    printf("Time - tacts of processor \n");
    printf("Memory - bytes \n\n");

    printf(
        "|Stack's|  Time of adding     |  Time of deletion   |       Memory        |\n");
    printf(
        "| size  |  array   |   list   |  array   |   list   |   array  |  list    |\n");
    printf(
        "|-------|----------|----------|----------|----------|----------|---------"
        "-|\n");

    for (size_t i = 1; i < 70000; i *= 2)
    {
        clock_t start, time_push_array = 0, time_push_list = 0, time_pop_array = 0,
                    time_pop_list = 0;

        for (size_t k = 0; k < counts; k++)
        {
            array_stack_t array;
            init_array(&array);
            list_stack_t *l = init_list_stack();

            start = clock();
            for (size_t j = 0; j < i; j++)
            push_array_item(&array);
            time_push_array += clock() - start;

            start = clock();
            for (size_t j = 0; j < i; j++)
            push_list_stack_t(l);
            time_push_list += clock() - start;

            double element;
            start = clock();
            for (size_t j = 0; j < i; j++)
                pop_array_item(&array);
      
            time_pop_array += clock() - start;

            start = clock();
            for (size_t j = 0; j < i; j++)
                pop_list_stack_t(l, &element);
            free_list_stack(l);

        time_pop_list += clock() - start;

    }

    printf("|%7zu|%10ld|%10ld|%10ld|%10ld|%10ld|%10ld|\n", i,
           time_push_array / counts, time_push_list / counts,
           time_pop_array / counts, time_pop_list / counts, size_array_stack(i),
           size_list_stack(i));
  }
  printf("Static array memory = %zu\n\n", size_array_stack(ARRAY_CAPACITY));

  return 0;
}

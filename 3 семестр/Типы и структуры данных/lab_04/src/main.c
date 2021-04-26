#include "utility.h"

int main(void)
{
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);

    array_stack_t array;
    init_array(&array);

    list_stack_t *list_stack = NULL;
    list_stack = init_list_stack();

    int choice = -1;
    while (choice)
    {
        system("clear");
        print_menu();
        get_choice(&choice, 0, 7);

        if (choice == 1)
        {
            print_array_stack(array);
            get_enter();          
        }
        else if (choice == 2)
        {
            add_array_item(&array);
            get_enter();
        }
        else if (choice == 3)
        {
            get_array_item(&array);
            get_enter();
        }
        else if (choice == 4)
        {
            print_list_stack(list_stack);
            get_enter();  
        }
        else if (choice == 5)
        {
            push_list_stack(list_stack);
            get_enter();
        }
        else if (choice == 6)
        {
            double element;

            if (!pop_list_stack(list_stack, &element))
                printf("\nAddress: %p   Element: %10lf\n", &element, element);
            get_enter();
        }
        else if (choice == 7)
        {
            compare_methods();
            get_enter();
        }
        else if (choice == 0)
        {
            system("clear");
            break;
        }
    }
    

    return EXIT_SUCCESS;
}

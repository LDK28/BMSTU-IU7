#include "polinom.h"

void list_free_all(polinom_t *head)
{
    if (head)
    {
        polinom_t *next;

        for (; head; head = next)
        {
            next = head->next;
            free(head);
        }
    }
}

void sorted_insert(polinom_t **head, polinom_t *element)
{
    element->next = NULL;

    if (*head == NULL)
    {
        *head = element;
        return;
    }

    polinom_t *cur = *head;
    polinom_t *previous = NULL;

    for (; cur->next && (element->degree <= cur->degree); cur = cur->next)
        previous = cur;

    if (!previous)
    {
        if (element->degree > cur->degree)
        {
            element->next = *head;
            *head = element;
        }
        else
            (*head)->next = element;
    } 
    else
    {
        if (!(cur->next) && (element->degree <= cur->degree))
            cur->next = element;
        else
        {
            element->next = cur;
            previous->next = element;
        }
    }
}

polinom_t *sort_polinom(polinom_t *head)
{
    if (!head)
        return NULL;

    polinom_t *new_head = NULL;
    polinom_t *tmp = head;
    head = head->next;

    while (tmp)
    {
        sorted_insert(&new_head, tmp);

        if (!head)
            tmp = NULL;
        else
        {
            tmp = head;
            head = head->next;
        }
    }

    return new_head;
}

void print_polinom(polinom_t *polinom)
{
    polinom_t *sorted_polinom = sort_polinom(polinom);
    for (; sorted_polinom; sorted_polinom = sorted_polinom->next)
        printf("%ld %ld ", sorted_polinom->coefficient, sorted_polinom->degree);
    puts("L");
}

int add_element_to_list(polinom_t **list, long coefficient, long degree)
{
    polinom_t *tmp = malloc(sizeof(polinom_t));
    if (!tmp) 
        return ALLOCATE_ERROR;

    tmp->next = *list;
    tmp->coefficient = coefficient;
    tmp->degree = degree;
    *list = tmp;

    return EXIT_SUCCESS;
}

int reverse(polinom_t **head)
{
    if (!head || !(*head))
        return EXIT_FAILURE;

    polinom_t *cur = *head;
    polinom_t *next, *previous = NULL;

    for (; cur; cur = next)
    {
        next = cur->next;
        cur->next = previous;
        previous = cur;
    }
    *head = previous;

    return EXIT_SUCCESS;
}

int get_action(int *action)
{
    char string[4];

    size_t i;
    for (i = 0; i < 3; ++i)
        *(string + i) = getchar();
    *(string + i) = 0;
    if (getchar() != '\n')
        return INCORRECT_ACTION_ERROR;

    if (strcmp(string, "val") == 0)
        *action = VAL;
    else if (strcmp(string, "ddx") == 0)
        *action = DDX;
    else if (strcmp(string, "sum") == 0)
        *action = SUM;
    else if (strcmp(string, "dvd") == 0)
        *action = DVD;
    else
        return INCORRECT_ACTION_ERROR;
    return EXIT_SUCCESS;
}

int get_polinom(polinom_t **polinom)
{
    *polinom = malloc(sizeof(polinom_t));
    polinom_t *cur = *polinom;
    cur->next = NULL;
    long tmp;
    int ch;
    int count = 0;
    
    while (1)
    {
        if (scanf("%ld", &tmp) != 1)
        {
            list_free_all(*polinom);
            return INCORRECT_DATA_ERROR;
        }

        if (count == 0)
        {
            cur->coefficient = tmp;
            count = 1;
        }
        else
        {
            cur->degree = tmp;
            count = 0;
        }

        ch = getchar();
        if (ch == '\n')
        {
            if (count != 0)
            {
                list_free_all(*polinom);
                return INCORRECT_DATA_ERROR;
            }
            cur->next = NULL;
            return EXIT_SUCCESS;
        }
        
        if (count == 0)
        {
            cur->next = malloc(sizeof(polinom_t));
            cur = cur->next;
            cur->next = NULL;
        }
    }
}

long val(polinom_t *polinom, long number)
{
    long result = 0;

    for (; polinom; polinom = polinom->next)
    {
        long tmp;
        if (polinom->degree == 0)
            tmp = 1;
        else
            tmp = number;

        for (long i = 2; i <= polinom->degree; ++i)
            tmp *= number;
        tmp *= polinom->coefficient;

        result += tmp;
    }
    
    return result;
}

polinom_t *ddx(polinom_t *polinom)
{
    if (!polinom)
        return NULL;
    
    polinom_t *polinom_ddx = NULL;
    long new_coefficient = 0;
    long new_degree = 0;
    while (polinom)
    {
        if (polinom->degree != 0)
        {
            new_coefficient = polinom->coefficient * polinom->degree;
            new_degree = polinom->degree - 1;
            if (add_element_to_list(&polinom_ddx, new_coefficient, new_degree) != EXIT_SUCCESS)
            {
                list_free_all(polinom_ddx);
                return NULL;
            }
        }
        polinom = polinom->next;
    }

    reverse(&polinom_ddx);

    return polinom_ddx;
}

polinom_t *sum(polinom_t *polinom1, polinom_t *polinom2)
{  
    if (!polinom1 && !polinom2)
        return NULL;

    polinom_t *result = NULL;

    while (polinom1 || polinom2)
    {
        if (polinom1 == NULL)
        {
            if (add_element_to_list(&result, polinom2->coefficient, polinom2->degree))
            {
                list_free_all(result);
                return NULL;
            }
            polinom2 = polinom2->next;
        }
        else if (polinom2 == NULL)
        {
            if (add_element_to_list(&result, polinom1->coefficient, polinom1->degree))
            {
                list_free_all(result);
                return NULL;
            }
            polinom1 = polinom1->next;
        }
        else if (polinom1->degree == polinom2->degree)
        {
            if (polinom1->coefficient + polinom2->coefficient != 0)
                if (add_element_to_list(&result, polinom1->coefficient + polinom2->coefficient, polinom1->degree))
                {
                    list_free_all(result);
                    return NULL;
                }
            polinom1 = polinom1->next;
            polinom2 = polinom2->next;
        }
        else if (polinom1->degree > polinom2->degree)
        {
            if (add_element_to_list(&result, polinom1->coefficient, polinom1->degree))
            {
                list_free_all(result);
                return NULL;
            }
            polinom1 = polinom1->next;
        }
        else if (polinom1->degree < polinom2->degree)
        {
            if (add_element_to_list(&result, polinom2->coefficient, polinom2->degree))
            {
                list_free_all(result);
                return NULL;
            }
            polinom2 = polinom2->next;
        }
    }

    if (!result)
        return NULL;

    reverse(&result);

    return result;
}

int dvd(polinom_t *polinom, polinom_t **even, polinom_t **odd)
{
    if (!polinom)
        return INCORRECT_DATA_ERROR;
        
    for (; polinom; polinom = polinom->next)
    {
        if (polinom->degree % 2 == 0)
        {
            if (add_element_to_list(even, polinom->coefficient, polinom->degree) != EXIT_SUCCESS)
            {
                list_free_all(*even);
                list_free_all(*odd);
                return ALLOCATE_ERROR;
            }
        }
        else
        {
            if (add_element_to_list(odd, polinom->coefficient, polinom->degree) != EXIT_SUCCESS)
            {
                list_free_all(*even);
                list_free_all(*odd);
                return ALLOCATE_ERROR;
            }
        }
    }

    if (!(*even) || !(*odd))
    {
        list_free_all(*even);
        list_free_all(*odd);
        return INCORRECT_DATA_ERROR;
    }
    reverse(even);
    reverse(odd);

    return EXIT_SUCCESS;
}

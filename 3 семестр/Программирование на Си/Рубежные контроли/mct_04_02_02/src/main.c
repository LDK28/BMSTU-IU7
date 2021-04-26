#include <stdlib.h>
#include <stdio.h>

// двусвязный список, в данных число типа double
typedef struct node
{
    struct node *previous;
    double number;
    struct node *next;
} node_t;


// Вход: указатель на голову списка типа node_t
// При передаче нулевого указателя функция завершает своё исполнение в самом начале
// Выход: ничего
void append_average(node_t **head)
{
    if (!head || !(*head))
        return;

    double average = 0;
    size_t count = 0;
    node_t *cur = *head;

    for (; cur->next || cur->next != *head; cur = cur->next)
    {
        average += cur->number;
        ++count;
    }
    
    average /= count;
    count /= 2;

    cur = *head;
    for (size_t i = 0; i < count; ++i)
        cur = cur->next;
        
    node_t *element = malloc(sizeof(node_t));

    element->previous = cur;
    element->next = cur->next;
    element->number = average;

    cur->next = element;
    cur->next->previous = element;
}
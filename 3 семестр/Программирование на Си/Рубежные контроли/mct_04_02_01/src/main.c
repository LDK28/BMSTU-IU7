#include <stdlib.h>
#include <stdio.h>

// двусвязный список, в данных число типа long
typedef struct node
{
    struct node *previous;
    long number;
    struct node *next;
} node_t;


// Вставка элемента по удалённости от ближайшего числа, кратного десяти, в отсортированный список.
// Проверка на зацикленность возложена на вызывающую сторону.
// Вход: указатель на указатель на голову списка типа node_t.
// Выход: ничего.
void sorted_insert(node_t **head, node_t *element)
{
    element->next = NULL;

    if (*head == NULL)
    {
        *head = element;
        return;
    }

    node_t *cur = *head;
    node_t *previous = NULL;

    for (; cur->next && (element->number % 5) >= (cur->number % 5); cur = cur->next)
        previous = cur;

    if (!previous)
    {
        if ((element->number % 5) < (cur->number % 5))
        {
            element->next = *head;
            *head = element;
        }
        else
            (*head)->next = element;
    } 
    else
    {
        if (!(cur->next) && (element->number) % 5 >= (cur->number % 5))
            cur->next = element;
        else
        {
            element->next = cur;
            previous->next = element;
        }
    }
}

// Сортировка списка по удалённости от ближайшего числа, кратного десяти.
// Проверка на зацикленность возложена на вызывающую сторону.
// Вход: указатель на голову списка типа node_t.
// Выход: голова отсортированного списка.
node_t *sort_ten(node_t *head)
{
    if (!head)
        return NULL;

    node_t *new_head = NULL;
    node_t *tmp = head;
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

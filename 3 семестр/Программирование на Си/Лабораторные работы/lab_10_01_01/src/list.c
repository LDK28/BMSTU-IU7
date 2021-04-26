#include "list.h"

void *pop_front(node_t **head)
{
    if (!head || !(*head) || !(*head)->data)
        return NULL;
    
    void *data = (*head)->data;

    node_t *tmp = *head;

    *head = tmp->next;

    free(tmp);

    return data;
}

void *pop_back(node_t **head)
{
    if (!head || !(*head) || !(*head)->data)
        return NULL;

    node_t *previous = NULL;
    node_t *cur = *head;
    void *data;

    for (; cur->next; cur = cur->next)
        previous = cur;

    if (previous)
        previous->next = NULL;
    else
        *head = NULL;
    
    data = cur->data;
    free(cur);

    return data;
}

void append(node_t **head_a, node_t **head_b)
{
    if (*head_b == NULL)
        return;
    if (*head_a == NULL)
        *head_a = *head_b;
    else
    {
        node_t *cur = *head_a;
        for (; cur->next; cur = cur->next);
        cur->next = *head_b;
    }
    *head_b = NULL;
}

node_t *node_create(void *data)
{
    node_t *node = malloc(sizeof(node_t));
    if (!node)
        return NULL;
        
    node->data = data;
    node->next = NULL;        
        
    return node;
}

void list_free_all(node_t *head)
{
    node_t *next;

    for (; head; head = next)
    {
        next = head->next;
        free(head->data);
        free(head);
    }
}

void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *))
{
    element->next = NULL;

    if (*head == NULL)
    {
        *head = element;
        return;
    }

    node_t *cur = *head;
    node_t *previous = NULL;

    for (; cur->next && comparator(element->data, cur->data) >= 0; cur = cur->next)
        previous = cur;

    if (!previous)
    {
        if (comparator(element->data, cur->data) < 0)
        {
            element->next = *head;
            *head = element;
        }
        else
            (*head)->next = element;
    } 
    else
    {
        if (!(cur->next) && comparator(element->data, cur->data) >= 0)
            cur->next = element;
        else
        {
            element->next = cur;
            previous->next = element;
        }
    }
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    if (!head)
        return NULL;

    node_t *new_head = NULL;
    node_t *tmp = head;
    head = head->next;

    while (tmp)
    {
        sorted_insert(&new_head, tmp, comparator);

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
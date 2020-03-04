/*****************************************************************************
* Copyright: 2020-2030, ***oak***
* file name: 
* Description: 
* Author: oak
* Version: v-0.0.1
* Date: 2020-03-01 10:45:40
* History: 
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include "zmlist.h"
#include "zmdigital.h"
#include "zmmalloc.h"

typedef struct node
{
    void *data;
    struct node *next;
    struct node *pre;
} node_t;

typedef struct list
{
    node_t *head;
    Zmlist_operator_t listOperator;
} list_t;

/*****************************************************
 * @brief default compare function
 * 
 * @param first_data 
 * @param second_data 
 * @return int 
 ******************************************************/
static int list_default_compare(void *first_data, void *second_data)
{
    long first_addr = (long)first_addr;
    long second_addr = (long)second_data;

    return compare(first_addr, second_addr);
}

static int list_default_equal(void *first_data, void *second_data)
{
    return first_data == second_data ? 0 : -1;
}

static int list_default_destory(void *data)
{
    free(data);
}

static node_t *new_node(void *data)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->data = data;
    node->next = NULL;
    node->pre = NULL;

    return node;
}

void list_create(list_t **list, Zmlist_operator_t *listOperator)
{
    list_t *newList = NULL;

    newList = zmsmalloc(sizeof(list_t), 0);
    if (newList == NULL)
    {
        return;
    }

    newList->listOperator.list_compare_func = (listOperator->list_compare_func == NULL ? list_default_compare : listOperator->list_compare_func);
    newList->listOperator.list_is_equal_func = (listOperator->list_is_equal_func == NULL ? list_default_equal : listOperator->list_is_equal_func);
    newList->listOperator.list_destory_func = (listOperator->list_destory_func == NULL ? list_default_destory : listOperator->list_destory_func);
}

int list_len(list_t *list)
{
    int i = 0;
    node_t *head = list->head;

    while (head)
    {
        head = head->next;
        i++;
    }

    return i;
}

int list_find(list_t *list, void *node_data)
{
    int i = -1;
    node_t *head = list->head;

    while ((head != NULL) && (list->listOperator.list_is_equal_func(head->data, node_data) == 0))
    {
        i++;
        head = head->next;
    }

    return head == NULL ? -1 : i;
}

void list_append(list_t *list, void *data)
{
    node_t *head = NULL;
    node_t *node = NULL;

    head = list->head;
    node = new_node(data);

    while ((head != NULL) && (head->next != NULL))
    {
        head = head->next;
    }

    if (head == NULL)
    {
        list->head = node;
        return;
    }

    node->pre = head;
    head->next = node;
}

int list_pop_tail(list_t *list, void **data_ptr)
{
    node_t *head = NULL;

    *data_ptr = NULL;
    head = list->head;

    if (head == NULL)
    {
        return -1;
    }

    while (head->next != NULL)
    {
        head = head->next;
    }

    if (head->pre->next != NULL)
    {
        head->pre->next = NULL;
    }

    *data_ptr = head->data;
    list->list_destory_func(head->data);
    free(head);

    return 0;
}

int list_pop(list_t *list, int pos, void **data_ptr)
{
    int i = 0;
    node_t *head = list->head;

    *data_ptr = NULL;
    if (list->head == NULL)
    {
        return -1;
    }

    head = list->head;
    while ((head != NULL) && (i++ != pos) && (head->next != NULL))
    {
        head = head->next;
    }

    if (head->next == NULL && (i != pos))
    {
        return -1;
    }

    // means first element
    if (head->pre->next != NULL)
    {
        head->pre->next = NULL;
    }

    return 1;
}

int list_iter(list_t *list, void **data_ptr, int *pos_ptr)
{
    static node_t *p = NULL;
    static int flag = 0;

    if (!flag)
    { //p init to head node when the first time
        p = list->head;
        flag = 1;
    }

    if (!p)
    {
        flag = 0;
        return 0;
    }
    *data_ptr = p->data;                   //get data
    *pos_ptr = get_index_by_node(list, p); //get index
    //move next
    p = p->next;
    return 1;
}

int list_get(list_t *list, int pos, void **data_ptr)
{
    node_t *head = list->head;
    int i = 0;

    for (; head; head = head->next, i++)
    {
        if (i == pos)
        {
            *data_ptr = head->data;
            return 1;
        }
    }
    return 0;
}

int list_set(list_t *list, int pos, void *data)
{
    node_t *t;
    int i;

    for (t = list->head, i = 0; t; t = t->next, i++)
    {
        if (i == pos)
        {
            t->data = data;
            return 1;
        }
    }
    return 0;
}

void list_extend(list_t *list_a, list_t *list_b)
{
    node_t *t;
    if (list_a->head == NULL)
        list_a->head = list_b->head;
    else
    {
        for (t = list_a->head; t->next; t = t->next)
            ;
        t->next = list_b->head;
    }
}

int list_swap(list_t *list, int pos_a, int pos_b)
{
    node_t *t, *a_pre = 0, *b_pre = 0, *a = 0, *b = 0, *head = list->head;
    int i;

    if (pos_a == 0)
        a = head;
    if (pos_b == 0)
        b = head;

    for (t = head, i = 0; t; t = t->next, i++)
    {
        if (i == pos_a - 1)
        {
            a_pre = t;
            a = t->next;
        }
        if (i == pos_b - 1)
        {
            b_pre = t;
            b = t->next;
        }
    }

    if (!a || !b)
        return 0; //wrong input position
    if (a == b)
        return 0; //do not swap the same node

    //change pre node's next
    if (a == head)
    {
        list->head = b;
        b_pre->next = a;
    }
    else if (b == head)
    {
        list->head = a;
        a_pre->next = b;
    }
    else
    {
        a_pre->next = b;
        b_pre->next = a;
    }

    //change a and b's next
    t = a->next;
    a->next = b->next;
    b->next = t;
    return 1;
}

void list_reverse(list_t *list)
{
    node_t *q = 0, *t, *m = list->head;
    for (; m; t = m->next, m->next = q, q = m, m = t)
        ;
    list->head = q;
}

int list_index(list_t *list, void *data)
{
    node_t *t = list->head;
    int i = 0;

    for (; t; t = t->next, i++)
    {
        if (t->data == data)
            return i;
    }
    return -1;
}

void list_cycle(list_t *list, void **data_ptr, int *pos_ptr)
{
    static node_t *p = NULL;
    if (!p)
        p = list->head;

    *data_ptr = p->data;                   //get data
    *pos_ptr = get_index_by_node(list, p); //get index
    //move
    p = p->next;
}

int list_from_array(list_t *list, void *ptr, int size, int len)
{
    if (list->head)
        return 0; //list is not empty

    int i;
    node_t *t;

    list->head = new_node(ptr); //init head

    for (i = 1, t = list->head; i < len; i++, t = t->next)
    {
        t->next = new_node(ptr + size * i);
    }
}
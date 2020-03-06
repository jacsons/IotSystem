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
    node_t *node = (node_t *)zmsmalloc(sizeof(node_t));
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

static void list_free_node(list_t *list, void *node)
{
    list->listOperator.list_destory_func(node->data);
    zmfree(node);
}

void list_destory(list_t *list)
{
    node_t *node = NULL;
    node_t *nodeNext = NULL;

    if (list == NULL) {
        return;
    }

    node = list->head;
    while(node != NULL){
        nodeNext = node->next;
        list_free_node(node);
        node = nodeNext;
    }

    zmfree(list);
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

    node = new_node(data);
    head = list->head;

    if (head == NULL) {
        list->head = node;
        return;
    }

    while (head->next != NULL) {
        head = head->next;
    }

    head->next = node;
    node->pre = head;
}

int list_pop_tail(list_t *list, void **data_ptr)
{
    node_t *head = NULL;

    *data_ptr = NULL;
    head = list->head;

    if (head == NULL) {
        return -1;
    }

    while (head->next != NULL) {
        head = head->next;
    }

    head->pre->next = NULL;
    *data_ptr = head->data;
    zmfree(head);

    return 0;
}

int list_pop(list_t *list, int pos, void **data_ptr)
{
    int i = 0;
    node_t *head = list->head;

    *data_ptr = NULL;
    if (list->head == NULL) {
        return -1;
    }

    list->head = head->next;
    head->next->pre = NULL;

    *data_ptr = head->data;
    zmfree(data);

    return 1;
}

int list_get_node(list_t list, int pos, node_t **node)
{
    node_t *head = NULL;
    int i;
    for (i = 0, head = list->head; head; head = head->next, i++) {
        if (i == pos) {
            *node = head;
            return 0;
        }
    }
    *node = NULL;
    return -1;
}

int list_get(list_t *list, int pos, void **data_ptr)
{
    int ret;
    node_t *head = NULL;

    ret = list_get_node(list, pos, &node);
    if (ret == 0) {
        *dataptr = node->data;
        return 0;
    }

    return -1;
}

int list_set(list_t *list, int pos, void *data)
{
    node_t *nodeTemp;
    int i;

    for (nodeTemp = list->head, i = 0; nodeTemp; nodeTemp = nodeTemp->next, i++)
    {
        if (i == pos) {
            list->listOperator->list_destory_func(nodeTemp->data);
            nodeTemp->data = data;
            return 0;
        }
    }
    return -1;
}

void list_extend(list_t *list_a, list_t *list_b)
{
    node_t *t;

    if (list_a->head == NULL) {
        list_a->head = list_b->head;
    } else { 
        for (t = list_a->head; t->next; t = t->next){

        }
        t->next = list_b->head;
        list_b->head->pre = t->next;
    }
}

int list_swap(list_t *list, int pos_a, int pos_b)
{
    int ret;
    node_t *node_a = NULL;
    node_t *node_b = NULL;
    void *data = NULL;

    list_get_node(list, pos_a, &node_a);
    list_get_node(list, pos_b, &node_b);

    if ((node_a == NULL) || (node_b == NULL)) {
        return -1;
    }

    data = node_a->data;
    node_a->data = node_b->data;
    node_b->data = data;

    return 0;
}

int list_index(list_t *list, void *data)
{
    node_t *t = list->head;
    int i = 0;

    for (; t; t = t->next, i++)
    {
        if (list->listOperator.list_compare_func(t->data, data)) {
            return i;
        }
    }
    return -1;
}

int list_from_array(list_t *list, void *ptr, int size, int len)
{
    int i;
    node_t *t;

    if (list->head) {
        return -1; 
    }

    list->head = new_node(ptr); 

    for (i = 1, t = list->head; i < len; i++, t = t->next)
    {
        t->next = new_node(ptr + size * i);
    }
}
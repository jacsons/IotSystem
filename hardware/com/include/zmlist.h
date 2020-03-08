/*****************************************************************************
 * Copyright: 2020-2030, ***oak***
 * file name:
 * Description:
 * Author: oak
 * Version: v-0.0.1
 * Date: 2020-03-01 10:45:40
 * History:
 ***************************************************************************/
#ifndef __ZM_LIST_H__
#define __ZM_LIST_H__

typedef int (*list_compare)(void *frist, void *second);
typedef int (*list_is_equal)(void *frist, void *second);
typedef void (*list_destory_func)(void *node);
typedef void (*list_node_ref_inc)(void *node);
typedef void (*list_node_fef_dec)(void *node);

typedef struct Zmlist_operator {
    list_compare list_compare_func;
    list_is_equal list_is_equal_func;
    list_destory_func list_destory_func;
} Zmlist_operator_t;
typedef struct node {
    void *data;
    struct node *next;
    struct node *pre;
} node_t;
typedef struct list {
    node_t *head;
    Zmlist_operator_t listoperator;
} list_t;

typedef struct list_iter_t_ {
    list_t *list;
    node_t *currentNode;
} list_iter_t;

/*****************************************************
 * @brief create list
 *
 * @param list outpurt value : a new list
 * @param listOperator list operator function
 ******************************************************/
void list_create(list_t **list, Zmlist_operator_t *listOperator);
void list_destory(list_t *list);
void list_append(list_t *list, void *data);
int list_len(list_t *list);
int list_get(list_t *list, int position, void **data_ptr);
int list_set(list_t *list, int pos, void *data);
int list_pop_tail(list_t *list, void **data_ptr);
int list_pop(list_t *list, int pos, void **data_ptr);
void list_extend(list_t *list_a, list_t *list_b);
int list_swap(list_t *list, int pos_a, int pos_b);
int list_index(list_t *list, void *data);
int list_from_array(list_t *list, void *ptr, int size, int len);

int list_iter_int(list_t *list, list_iter_t **list_iter);
node_t *list_iter_next(list_iter_t *list_iter);
int list_iter_destory(list_iter_t *list_iter);

#endif // __ZM_LIST_H__

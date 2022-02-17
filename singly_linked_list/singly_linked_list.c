/*********************************************************
 * Singly Linked List Data Structure
 * -------------------------------------------------------
 *      Implementation in C
 *      elements are stored By reference.
 *
 * Ziv Kaplan
 * February 2022
 * -------------------------------------------------------
 * Please read the header file for the complete API.
 ********************************************************/

#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert() */
#include <string.h> /* memset() */

#include "singly_linked_list.h" /* header of this source file */

struct list
{
    struct node *first;
    struct node last;
    size_t size;
};

typedef struct node
{
    struct node *next;
    void *data;
} node_t;

/*********************************
 * Static Functions Declarations
 ********************************/
static void SwapData(iter_t iter1, iter_t iter2);

/*********************************
 * API Functions Definitions
 ********************************/
list_t *CreateList(void)
{
    list_t *new_list = malloc(sizeof(list_t));
    if (!new_list)
    {
        return NULL;
    }

    /* Initialize members */
    memset(new_list, 0, sizeof(list_t));
    new_list->first = &(new_list->last);
    new_list->last.data = NULL;
    new_list->last.next = NULL;
    new_list->size = 0;

    return new_list;
}

void DestroyList(list_t *list)
{
    if (!list)
    {
        return;
    }
    iter_t current = GetNode(ListBegin(list));
    iter_t next = NULL;

    while (current != ListEnd(list))
    {
        next = GetNext(current);

        memset(current, 0, sizeof(node_t));
        free(current);

        current = next;
    }

    memset(list, 0, sizeof(list_t));
    free(list);

    list = NULL;
}

iter_t Insert(list_t *list, iter_t iter, const void *data)
{
    assert(list);
    assert(iter);

    iter_t duplicated_iter = InsertAfter(list, iter, GetData(iter));
    if (IsSameIterator(duplicated_iter, ListEnd(list)))
    {
        return ListEnd(list);
    }

    iter->data = data;
    return iter;
}

iter_t InsertAfter(list_t *list, iter_t iter, const void *data)
{
    assert(list);
    assert(iter);

    iter_t next_node = iter->next;
    iter_t new_node = CreateNode(data, next_node); /* TODO: implement */
    if (!new_node)
    {
        return ListEnd(list);
    }

    iter->next = new_node;

    return new_node;
}

iter_t Remove(list_t *list, iter_t iter)
{
    assert(list);
    assert(iter);

    iter_t next_iter = iter->next;
    SwapData(iter, next_iter);
    iter->next = next_iter->next;

    memset(iter, 0, sizeof(node_t));
    free(iter);
    iter = NULL;

    return next_iter;
}

void *GetData(const iter_t iter)
{
    assert(iter);

    return iter->data;
}

void SetData(iter_t iter, const void *data)
{
    assert(iter);

    iter->data = data;
}

iter_t ListBegin(const list_t *list)
{
    assert(list);

    return list->first;
}

iter_t ListEnd(const list_t *list)
{
    assert(list);

    return (&(list->last));
}

iter_t ListNext(const iter_t iter)
{
    assert(iter);

    return iter->next;
}

int IsSameIterator(const iter_t iter1, const iter_t iter2)
{
    assert(iter1);
    assert(iter2);

    return iter1 == iter2;
}

iter_t ListFind(const list_t *list, void *param,
                int (*is_match_func)(const void *iterated_data, const void *param))
{
    assert(list);
    assert(is_match_func);
    iter_t iter = NULL;

    for (iter = ListBegin(list);
         iter != ListEnd(list);
         iter = ListNext(iter))
    {
        if (is_match_func(iter->data, param))
        {
            break;
        }
    }

    return iter;
}

iter_t ListForEach(list_t *list, void *param,
                   int (*oper_func)(void *iterated_data, void *param))
{
    assert(list);
    assert(oper_func);
    iter_t iter = NULL;

    for (iter = ListBegin(list);
         iter != ListEnd(list);
         iter = ListNext(iter))
    {
        if (oper_func(iter->data, param))
        {
            break;
        }
    }

    return iter;
}

size_t ListGetSize(const list_t *list)
{
    assert(list);

    return list->size;
}

int ListIsEmpty(const list_t *list)
{
    return 0 == list->size; /* also possible: list->first == &(list->end) */
}

/*********************************
 * Static Functions Definitions
 ********************************/
static void SwapData(iter_t iter1, iter_t iter2)
{
    assert(iter1);
    assert(iter2);

    void *iter1_data = GetData(iter1);
    SetData(iter1, GetData(iter2));
    SetData(iter2, iter1_data);
}

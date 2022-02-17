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

iter_t Insert(list_t list, iter_t iter, const void *data);
iter_t InsertAfter(list_t list, iter_t iter, const void *data);

iter_t Remove(list_t list, iter_t iter);
iter_t RemoveAfter(list_t list, iter_t iter);

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

void SLListAppend(list_t *dest, list_t *src);
/* Concatenate src to the end of dest */

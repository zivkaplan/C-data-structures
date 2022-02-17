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
#include <stdio.h>
#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert() */
#include <string.h> /* memset() */

#include "singly_linked_list.h" /* header of this source file */

typedef struct node
{
    struct node *next;
    void *data;
} node_t;

struct list
{
    struct node *last;
    struct node *first;
};

/*********************************
 * Static Functions Declarations
 ********************************/
static node_t *CreateNode(const void *data, node_t *next_node);
static void SwapData(sll_iter_t iter1, sll_iter_t iter2);
static void SetNext(sll_iter_t iter, const sll_iter_t next);

/*********************************
 * API Functions Definitions
 ********************************/
list_t *SinglyListCreate(void)
{
    void *mem_pool = malloc(sizeof(list_t) + sizeof(node_t));
    if (!mem_pool)
    {
        return NULL;
    }

    memset(mem_pool, 0, sizeof(list_t) + sizeof(node_t));

    list_t *new_list = (list_t *)mem_pool;
    node_t *dummy_node = (node_t *)((char *)mem_pool + sizeof(list_t));

    /* Initialize members */
    new_list->first = dummy_node;
    new_list->last = dummy_node;

    dummy_node->data = NULL;
    dummy_node->next = NULL;

    return new_list;
}

void SinglyListDestroy(list_t *list)
{
    if (!list)
    {
        return;
    }

    sll_iter_t current = SinglyListBegin(list);
    sll_iter_t next = NULL;

    while (current != SinglyListEnd(list))
    {
        next = SinglyListNext(current);

        memset(current, 0, sizeof(node_t));
        free(current);

        current = next;
    }

    memset(list, 0, sizeof(list_t));
    free(list);

    list = NULL;
}

sll_iter_t SinglyListInsert(list_t *list, sll_iter_t iter, const void *data)
{
    assert(list);
    assert(iter);

    node_t *new_node = CreateNode(SinglyListGetData(iter), iter);
    if (!new_node)
    {
        return SinglyListEnd(list);
    }

    if (SinglyListIsSameIterator(iter, SinglyListEnd(list)))
    {
        list->last = new_node;
    }

    SinglyListSetData(iter, data);
    SetNext(iter, new_node);

    return iter;
}

sll_iter_t SinglyListInsertAfter(list_t *list, sll_iter_t iter, const void *data)
{
    assert(list);
    assert(iter);

    node_t *new_node = CreateNode(data, SinglyListNext(iter));
    if (!new_node)
    {
        return SinglyListEnd(list);
    }

    SetNext(iter, new_node);

    return new_node;
}

sll_iter_t SinglyListRemove(list_t *list, sll_iter_t iter)
{
    assert(list);
    assert(iter);

    sll_iter_t next_iter = SinglyListNext(iter);
    SwapData(iter, next_iter);
    SetNext(iter, SinglyListNext(next_iter));

    memset(iter, 0, sizeof(node_t));
    free(iter);
    iter = NULL;

    return next_iter;
}

sll_iter_t SinglyListRemoveAfter(list_t *list, sll_iter_t iter)
{
    assert(list);
    assert(iter);

    sll_iter_t iter_to_remove = SinglyListNext(iter);
    sll_iter_t next_after_remove = SinglyListNext(iter_to_remove);
    SetNext(iter, next_after_remove);

    memset(iter_to_remove, 0, sizeof(node_t));
    free(iter_to_remove);
    iter_to_remove = NULL;

    return iter;
}

void *SinglyListGetData(const sll_iter_t iter)
{
    assert(iter);

    return iter->data;
}

void SinglyListSetData(sll_iter_t iter, const void *data)
{
    assert(iter);

    iter->data = (void *)data;
}

sll_iter_t SinglyListBegin(const list_t *list)
{
    assert(list);

    return list->first;
}

sll_iter_t SinglyListEnd(const list_t *list)
{
    assert(list);

    return list->last;
}

sll_iter_t SinglyListNext(const sll_iter_t iter)
{
    assert(iter);

    return iter->next;
}

int SinglyListIsSameIterator(const sll_iter_t iter1, const sll_iter_t iter2)
{
    assert(iter1);
    assert(iter2);

    return iter1 == iter2;
}

sll_iter_t SinglyListFind(const list_t *list, void *param,
                          int (*is_match_func)(const void *iterated_data, const void *param))
{
    assert(list);
    assert(is_match_func);

    sll_iter_t iter = NULL;

    for (iter = SinglyListBegin(list);
         iter != SinglyListEnd(list);
         iter = SinglyListNext(iter))
    {
        if (is_match_func(iter->data, param))
        {
            break;
        }
    }

    return iter;
}

sll_iter_t SinglyListForEach(list_t *list, void *param,
                             int (*oper_func)(void *iterated_data, void *param))
{
    assert(list);
    assert(oper_func);
    sll_iter_t iter = NULL;

    for (iter = SinglyListBegin(list);
         iter != SinglyListEnd(list);
         iter = SinglyListNext(iter))
    {
        if (oper_func(iter->data, param))
        {
            break;
        }
    }

    return iter;
}

size_t SinglyListGetSize(const list_t *list)
{
    assert(list);

    size_t size = 0;

    for (sll_iter_t iter = SinglyListBegin(list);
         iter != SinglyListEnd(list);
         iter = SinglyListNext(iter))
    {
        size++;
    }

    return size;
}

int SinglyListIsEmpty(const list_t *list)
{
    return SinglyListIsSameIterator(list->first, list->last);
}

/*********************************
 * Static Functions Definitions
 *********************************/

static node_t *CreateNode(const void *data, node_t *next_node)
{
    node_t *new_node = malloc(sizeof(node_t));
    if (!new_node)
    {
        return NULL;
    }

    memset(new_node, 0, sizeof(node_t));
    new_node->data = (void *)data;
    new_node->next = next_node;

    return new_node;
}

static void SwapData(sll_iter_t iter1, sll_iter_t iter2)
{
    assert(iter1);
    assert(iter2);

    void *iter1_data = SinglyListGetData(iter1);
    SinglyListSetData(iter1, SinglyListGetData(iter2));
    SinglyListSetData(iter2, iter1_data);
}

static void SetNext(sll_iter_t iter, const sll_iter_t next)
{
    assert(iter);

    iter->next = next;
}

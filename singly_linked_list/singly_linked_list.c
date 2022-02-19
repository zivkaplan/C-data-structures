/*********************************************************
 * Singly Linked List Data Structure
 * -------------------------------------------------------
 *      Implementation in C
 *      Elements are stored By reference.
 *
 * Ziv Kaplan
 * February 2022
 * -------------------------------------------------------
 * Please refer to the header file for the complete API.
 ********************************************************/

#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert() */
#include <string.h> /* memset() */

#include "singly_linked_list.h" /* header of this source file */

typedef struct sll_node
{
    struct sll_node *next;
    void *data;
} sll_node_t;

struct singly_list
{
    struct sll_node *last;
    struct sll_node *first;
};

static const size_t LIST_W_DUMMY_SIZE = sizeof(singly_list_t) + sizeof(sll_node_t);

/*********************************
 * Static Functions Declarations
 ********************************/
static sll_node_t *CreateNode(const void *data, sll_node_t *next_node);
static void SwapData(sll_iter_t iter1, sll_iter_t iter2);
static void SetNext(sll_iter_t iter, const sll_iter_t next);

/*********************************
 * API Functions Definitions
 ********************************/
singly_list_t *SinglyListCreate(void)
{
    void *mem_pool = malloc(LIST_W_DUMMY_SIZE);
    if (!mem_pool)
    {
        return NULL;
    }

    memset(mem_pool, 0, LIST_W_DUMMY_SIZE);

    singly_list_t *new_list = (singly_list_t *)mem_pool;
    sll_node_t *dummy_node = (sll_node_t *)(new_list + 1);

    /* Initialize members */
    new_list->first = dummy_node;
    new_list->last = dummy_node;

    dummy_node->data = NULL;
    dummy_node->next = NULL;

    return new_list;
}

void SinglyListDestroy(singly_list_t *list)
{
    if (!list)
    {
        return;
    }

    sll_iter_t current = SinglyListBegin(list);
    sll_iter_t next = NULL;

    while (!SinglyListIsSameIterator(SinglyListEnd(list), current))
    {
        next = SinglyListNext(current);

        memset(current, 0, sizeof(sll_node_t));
        free(current);

        current = next;
    }

    memset(list, 0, LIST_W_DUMMY_SIZE);
    free(list);

    list = NULL;
}

sll_iter_t SinglyListInsert(singly_list_t *list, sll_iter_t iter, const void *data)
{
    assert(list);
    assert(iter);

    sll_node_t *new_node = CreateNode(SinglyListGetData(iter), SinglyListNext(iter));
    if (!new_node)
    {
        return SinglyListEnd(list);
    }

    SinglyListSetData(iter, data);
    SetNext(iter, new_node);

    if (SinglyListIsSameIterator(list->last, iter))
    {
        list->last = new_node;
    }

    return iter;
}

sll_iter_t SinglyListInsertAfter(singly_list_t *list, sll_iter_t iter, const void *data)
{
    assert(list);
    assert(iter);

    sll_node_t *new_node = CreateNode(data, SinglyListNext(iter));
    if (!new_node)
    {
        return SinglyListEnd(list);
    }

    SetNext(iter, new_node);

    return new_node;
}

sll_iter_t SinglyListRemove(singly_list_t *list, sll_iter_t iter)
{
    assert(list);
    assert(iter);

    sll_iter_t iter_to_remove = SinglyListNext(iter);
    SwapData(iter, iter_to_remove);
    SetNext(iter, SinglyListNext(iter_to_remove));

    if (SinglyListIsSameIterator(list->last, iter_to_remove))
    {
        list->last = iter;
    }

    memset(iter_to_remove, 0, sizeof(sll_node_t));
    free(iter_to_remove);
    iter_to_remove = NULL;

    return SinglyListNext(iter);
}

sll_iter_t SinglyListRemoveAfter(singly_list_t *list, sll_iter_t iter)
{
    assert(list);
    assert(iter);

    sll_iter_t iter_to_remove = SinglyListNext(iter);
    sll_iter_t next_after_remove = SinglyListNext(iter_to_remove);
    SetNext(iter, next_after_remove);

    memset(iter_to_remove, 0, sizeof(sll_node_t));
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

sll_iter_t SinglyListBegin(const singly_list_t *list)
{
    assert(list);

    return list->first;
}

sll_iter_t SinglyListEnd(const singly_list_t *list)
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

sll_iter_t SinglyListFind(const singly_list_t *list, void *param,
                          int (*is_match_func)(const void *iterated_data, const void *param))
{
    assert(list);
    assert(is_match_func);

    sll_iter_t iter = NULL;

    for (iter = SinglyListBegin(list);
         !SinglyListIsSameIterator(SinglyListEnd(list), iter);
         iter = SinglyListNext(iter))
    {
        if (is_match_func(iter->data, param))
        {
            break;
        }
    }

    return iter;
}

sll_iter_t SinglyListForEach(singly_list_t *list, void *param,
                             int (*operation_func)(void *iterated_data, void *param))
{
    assert(list);
    assert(operation_func);
    sll_iter_t iter = NULL;

    for (iter = SinglyListBegin(list);
         !SinglyListIsSameIterator(SinglyListEnd(list), iter);
         iter = SinglyListNext(iter))
    {
        if (operation_func(iter->data, param))
        {
            break;
        }
    }

    return iter;
}

size_t SinglyListGetSize(const singly_list_t *list)
{
    assert(list);

    size_t size = 0;

    for (sll_iter_t iter = SinglyListBegin(list);
         !SinglyListIsSameIterator(SinglyListEnd(list), iter);
         iter = SinglyListNext(iter))
    {
        size++;
    }

    return size;
}

int SinglyListIsEmpty(const singly_list_t *list)
{
    return SinglyListIsSameIterator(list->first, list->last);
}

/*********************************
 * Static Functions Definitions
 *********************************/

static sll_node_t *CreateNode(const void *data, sll_node_t *next_node)
{
    sll_node_t *new_node = malloc(sizeof(sll_node_t));
    if (!new_node)
    {
        return NULL;
    }

    memset(new_node, 0, sizeof(sll_node_t));
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

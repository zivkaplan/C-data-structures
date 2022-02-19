/*********************************************************
 * Doubly Linked List Data Structure
 * -------------------------------------------------------
 *      Implementation in C.
 *      Elements are stored By reference.
 *
 * Ziv Kaplan
 * February 2022
 * -------------------------------------------------------
 * Please refer to the header file for the complete API.
 ********************************************************/

#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* memset() */
#include <assert.h> /* assert() */

#include "doubly_linked_list.h" /* header of the current source file */

struct doubly_list
{
    struct dll_node *first;
    struct dll_node *last;
};

typedef struct dll_node
{
    struct dll_node *next;
    struct dll_node *prev;
    void *data;
} dll_node_t;

static const size_t LIST_W_DUMMY_SIZE = sizeof(doubly_list_t) + sizeof(dll_node_t);

doubly_list_t *DoublyListCreate(void)
{

    void *memory_pool = malloc(LIST_W_DUMMY_SIZE);
    if (!memory_pool)
    {
        return NULL;
    }

    memset(memory_pool, 0, LIST_W_DUMMY_SIZE);

    doubly_list_t *new_list = (doubly_list_t *)memory_pool;
    dll_node_t *dummy_node = (dll_node_t *)(new_list + 1);

    /* Initialize members */
    new_list->first = dummy_node;
    new_list->last = dummy_node;

    dummy_node->data = NULL;
    dummy_node->prev = NULL;
    dummy_node->next = NULL;

    return new_list;
}

void DoublyListDestroy(doubly_list_t *list)
{
    if (!list)
    {
        return;
    }
    dll_iter_t iter = DoublyListBegin(list);
    dll_iter_t list_end_iter = DoublyListEnd(list);

    while (!DoublyListIsSameIterator(iter, list_end_iter))
    {
        dll_iter_t next_iter = DoublyListNext(iter);
        memset(iter, 0, sizeof(dll_node_t));
        free(iter);

        iter = next_iter;
    }
    iter = NULL;
}

dll_iter_t DoublyListBegin(const doubly_list_t *list)
{
    assert(list);

    return list->first;
}

dll_iter_t DoublyListEnd(const doubly_list_t *list)
{
    assert(list);

    return list->last;
}

dll_iter_t DoublyListNext(dll_iter_t iter)
{
    assert(iter);

    return iter->next;
}

dll_iter_t DoublyListPrev(dll_iter_t iter)
{
    assert(iter);

    return iter->prev;
}

int DoublyListIsEmpty(const doubly_list_t *list)
{
    assert(list);

    return DoublyListIsSameIterator(DoublyListBegin(list), DoublyListEnd(list));
}

void *DoublyListGetData(dll_iter_t iter)
{
    assert(iter);

    return iter->data;
}

void DoublyListSetData(dll_iter_t iter, const void *data)
{
    assert(iter);

    iter->data = (void *)data;
}

int DoublyListIsSameIterator(const dll_iter_t iter1, const dll_iter_t iter2)
{
    assert(iter1);
    assert(iter2);

    return iter1 == iter2;
}

size_t DoublyListSize(const doubly_list_t *list)
{
    assert(list);

    size_t size = 0;
    dll_iter_t iter = DoublyListBegin(list);
    dll_iter_t list_end_iter = DoublyListEnd(list);

    for (; !DoublyListIsSameIterator(iter, list_end_iter);
         iter = DoublyListNext(iter))
    {
        size++;
    }

    return size;
}

/*
dll_iter_t DoublyListInsert(doubly_list_t list, dll_iter_t iter, void *data);
dll_iter_t DoublyListRemove(doubly_list_t list, dll_iter_t iter);

dll_iter_t DoublyListFind(dll_iter_t from_iter, dll_iter_t to_iter,
                          void *param,
                          int (*is_match)(const void *data, const void *param));
int DoublyListFindAll(const doubly_list_t *list,
                      void *param,
                      int (*is_match)(const void *data, const void *param), doubly_list_t *output_list);

int DoublyListForEach(dll_iter_t from_iter, dll_iter_t to_iter,
                      void *param,
                      int (*operation_func)(void *data, void *param));
*/

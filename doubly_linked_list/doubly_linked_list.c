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
    struct dll_node *dummy_first;
    struct dll_node *last;
};

typedef struct dll_node
{
    struct dll_node *next;
    struct dll_node *prev;
    void *data;
} dll_node_t;

static const size_t LIST_W_DUMMIES_SIZE = sizeof(doubly_list_t) +
                                          (sizeof(dll_node_t) * 2);

static void SetPrev(dll_iter_t iter, const dll_iter_t prev);
static void SetNext(dll_iter_t iter, const dll_iter_t next);

static dll_node_t *CreateNode(const void *data, const dll_node_t *prev_node,
                              const dll_node_t *next_node);

doubly_list_t *DoublyListCreate(void)
{

    void *memory_pool = malloc(LIST_W_DUMMIES_SIZE);
    if (!memory_pool)
    {
        return NULL;
    }

    memset(memory_pool, 0, LIST_W_DUMMIES_SIZE);

    doubly_list_t *new_list = (doubly_list_t *)memory_pool;
    dll_node_t *first_dummy = (dll_node_t *)(new_list + 1);
    dll_node_t *last_dummy = first_dummy + 1;

    /* Initialize members */
    new_list->dummy_first = first_dummy;
    new_list->last = last_dummy;

    first_dummy->data = NULL;
    first_dummy->prev = NULL;
    first_dummy->next = last_dummy;

    last_dummy->data = NULL;
    last_dummy->prev = first_dummy;
    last_dummy->next = NULL;

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

    memset(list, 0, sizeof(LIST_W_DUMMIES_SIZE));
    free(list);
    list = NULL;
}

dll_iter_t DoublyListInsert(doubly_list_t *list, dll_iter_t iter, const void *data)
{
    assert(list);
    assert(iter);

    dll_iter_t new_node = CreateNode(data, DoublyListPrev(iter), iter);
    if (!new_node)
    {
        return DoublyListEnd(list);
    }

    SetNext(DoublyListPrev(iter), new_node);
    SetPrev(iter, new_node);

    return new_node;
}

dll_iter_t DoublyListRemove(doubly_list_t *list, dll_iter_t iter)
{
    assert(list);
    assert(iter);

    dll_iter_t next_iter = DoublyListNext(iter);
    dll_iter_t prev_iter = DoublyListPrev(iter);

    SetNext(prev_iter, next_iter);
    SetPrev(next_iter, prev_iter);

    memset(iter, 0, sizeof(dll_node_t));
    free(iter);
    iter = NULL;

    return next_iter;
}

dll_iter_t DoublyListBegin(const doubly_list_t *list)
{
    assert(list);

    return DoublyListNext(list->dummy_first);
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

size_t DoublyListGetSize(const doubly_list_t *list)
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

dll_iter_t DoublyListFind(const doubly_list_t *list, void *param,
                          int (*is_match)(const void *data, const void *param))
{
    assert(list);
    assert(is_match);

    dll_iter_t iter = DoublyListBegin(list);
    dll_iter_t list_end_iter = DoublyListEnd(list);

    for (; !DoublyListIsSameIterator(iter, list_end_iter);
         iter = DoublyListNext(iter))
    {
        if (is_match(DoublyListGetData(iter), param))
        {
            break;
        }
    }

    return iter;
}

dll_iter_t DoublyListForEach(doubly_list_t *list, void *param,
                             int (*operation_func)(void *data, void *param))
{
    assert(list);
    assert(operation_func);

    dll_iter_t iter = DoublyListBegin(list);
    dll_iter_t list_end_iter = DoublyListEnd(list);

    for (; !DoublyListIsSameIterator(iter, list_end_iter);
         iter = DoublyListNext(iter))
    {
        if (operation_func(DoublyListGetData(iter), param))
        {
            break;
        }
    }

    return iter;
}

int DoublyListFindAll(const doubly_list_t *list, void *param,
                      int (*is_match)(const void *data, const void *param), doubly_list_t *output_list)
{
    assert(list);
    assert(is_match);
    assert(output_list);

    dll_iter_t iter = DoublyListBegin(list);
    dll_iter_t list_end_iter = DoublyListEnd(list);

    for (; !DoublyListIsSameIterator(iter, list_end_iter);
         iter = DoublyListNext(iter))
    {
        const void *current_data = DoublyListGetData(iter);
        if (is_match(current_data, param))
        {
            dll_iter_t result = DoublyListInsert(output_list,
                                                 DoublyListEnd(output_list),
                                                 current_data);

            if (DoublyListIsSameIterator(result, DoublyListEnd(output_list)))
            {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}

static dll_node_t *CreateNode(const void *data, const dll_node_t *prev_node, const dll_node_t *next_node)
{
    dll_node_t *new_node = malloc(sizeof(dll_node_t));
    if (!new_node)
    {
        return NULL;
    }

    memset(new_node, 0, sizeof(dll_node_t));
    new_node->data = (void *)data;
    new_node->prev = (dll_node_t *)prev_node;
    new_node->next = (dll_node_t *)next_node;

    return new_node;
}

static void SetNext(dll_iter_t iter, const dll_iter_t next)
{
    assert(iter);

    iter->next = next;
}

static void SetPrev(dll_iter_t iter, const dll_iter_t prev)
{
    assert(iter);

    iter->prev = prev;
}

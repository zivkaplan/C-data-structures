/***********************************
 * Queue Data Structure
 * ------------------------
 *      Implementation in C
 *      elements are stored By reference.
 *      built upon linked list implementation.
 *
 * Ziv Kaplan
 * February 2022
 **********************************/

#include <stdlib.h> /* EXIT_SUCCESS, EXIT_FAILURE, malloc(), free() */
#include <string.h> /* memset() */
#include <assert.h> /* assert() */

#include "singly_linked_list.h" /* Create(), Destroy(), IsEmpty(), GetSize(),
                                    TODO: ADD ALL */
#include "queue.h"              /* header of the current source file */

struct queue
{
    singly_list_t *list;
};

queue_t *QueueCreate(void)
{
    queue_t *new_queue = malloc(sizeof(queue_t));
    singly_list_t *new_list = SinglyListCreate();
    if (!new_queue || !new_list)
    {
        free(new_queue);
        SinglyListDestroy(new_list);

        return NULL;
    }

    new_queue->list = new_list;
    return new_queue;
}

void QueueDestroy(queue_t *queue)
{
    if (!queue)
    {
        return;
    }

    SinglyListDestroy(queue->list);

    memset(queue, 0, sizeof(queue_t));
    free(queue);
    queue = NULL;
}

int QueueIsEmpty(const queue_t *queue)
{
    assert(queue);

    return SinglyListIsEmpty(queue->list);
}

size_t QueueGetSize(const queue_t *queue)
{
    assert(queue);

    return SinglyListGetSize(queue->list);
}

void *QueuePeek(const queue_t *queue)
{
    assert(queue);

    return SinglyListGetData(SinglyListBegin(queue->list));
}

int QueueEnqueue(queue_t *queue, void *data)
{
    assert(queue);

    singly_list_t *list_from_queue = queue->list;
    sll_iter_t result = SinglyListInsert(list_from_queue,
                                         SinglyListEnd(list_from_queue), data);

    if (SinglyListIsSameIterator(result, SinglyListEnd(list_from_queue)))
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void QueueDequeue(queue_t *queue)
{
    assert(queue);

    singly_list_t *list_from_queue = queue->list;

    SinglyListRemove(list_from_queue, SinglyListBegin(list_from_queue));
}

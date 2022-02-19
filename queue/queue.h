#ifndef __QUEUE_H__
#define __QUEUE_H__

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

#include <stddef.h> /* size_t */

typedef struct queue queue_t;

queue_t *QueueCreate(void);
/* returns NULL on failure */

void QueueDestroy(queue_t *queue);

int QueueEnqueue(queue_t *queue, void *data);
/* return 0 for success, 1 for failure*/
void QueueDequeue(queue_t *queue);
/* Calling Dequeue() on empty queue is undefined */

void *QueuePeek(const queue_t *queue);

size_t QueueSize(const queue_t *queue);
int QueueIsEmpty(const queue_t *queue);

#endif /* __QUEUE_H__ */
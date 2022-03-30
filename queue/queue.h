#ifndef __ZK_QUEUE_H__
#define __ZK_QUEUE_H__

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

/* returns NULL on failure */
queue_t *QueueCreate(void);

/* Calling Destroy(NULL) is valid */
void QueueDestroy(queue_t *queue);

/* return 0 for success, 1 for failure*/
int QueueEnqueue(queue_t *queue, void *data);

/* Calling Dequeue() on empty queue is undefined */
void QueueDequeue(queue_t *queue);

/* Calling Peek() on empty queue is undefined */
void *QueuePeek(const queue_t *queue);

size_t QueueGetSize(const queue_t *queue);
int QueueIsEmpty(const queue_t *queue);

#endif /* __ZK_QUEUE_H__ */
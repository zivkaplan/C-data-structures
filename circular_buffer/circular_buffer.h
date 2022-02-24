#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

/***********************************
 * Circular Buffer Data Structure
 * ------------------------
 *      Implementation in C
 *      elements are stored By value.
 *
 * Ziv Kaplan
 * February 2022
 **********************************/

#include <sys/types.h> /* size_t, ssize_t */

typedef struct circular_buffer circ_buff_t;

circ_buff_t *CircBuffCreate(size_t capacity_in_bytes);
/*
Returns NULL on failure.
capacity_in_bytes == 0 is undefined.
*/

void CircBuffDestroy(circ_buff_t *circ_buff);
/* Calling Destroy(NULL) is valid */

ssize_t CircBuffGet(circ_buff_t *circ_buff, void *dest, size_t n_bytes);
/* Get() from an empty buffer is undefined */

ssize_t CircBufPut(circ_buff_t *circ_buff, const void *src, size_t count);
/*
On success, returns number of bytes written to buffer.
Otherwise, return -1.
*/

size_t CircBuffCapacity(const circ_buff_t *circ_buff);
size_t CircBuffFreeSpaceLeft(const circ_buff_t *circ_buff);
int CircBuffIsEmpty(const circ_buff_t *circ_buff);

#endif /* __CIRCULAR_BUFFER_H__ */
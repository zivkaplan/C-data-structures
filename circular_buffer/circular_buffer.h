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

/*
Returns NULL on failure.
capacity_in_bytes == 0 is undefined.
*/
circ_buff_t *CircBuffCreate(size_t capacity_in_bytes);

/* Calling Destroy(NULL) is valid */
void CircBuffDestroy(circ_buff_t *circ_buff);

/* returns the number of bytes read from the buffer. */
size_t CircBuffRead(circ_buff_t *circ_buff, void *dest, size_t n_bytes);

/* returns the number of bytes written to the buffer. */
size_t CircBuffWrite(circ_buff_t *circ_buff, const void *src, size_t count);

size_t CircBuffCapacity(const circ_buff_t *circ_buff);
size_t CircBuffFreeSpaceLeft(const circ_buff_t *circ_buff);
int CircBuffIsEmpty(const circ_buff_t *circ_buff);

#endif /* __CIRCULAR_BUFFER_H__ */
/*********************************************************
 * Circular Buffer Data Structure
 * -------------------------------------------------------
 *      Implementation in C.
 *      Elements are stored By value.
 *
 * Ziv Kaplan
 * February 2022
 * -------------------------------------------------------
 * Please refer to the header file for the complete API.
 ********************************************************/

#include <assert.h> /* assert() */
#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* memcpy() */

#include "circular_buffer.h" /* header of the current source file */

struct circular_buffer
{
    size_t actual_capacity;
    /*
    user's requested capacity + 1.
    */
    size_t write_idx;
    size_t read_idx;
    /*
    is empty: write_idx == read_idx
    is full: (write_idx + 1) % actual_capacity == read_idx
    */

    char arr[1];
};

circ_buff_t *CircBuffCreate(size_t capacity_in_bytes)
{
    assert(capacity_in_bytes);

    size_t size = sizeof(circ_buff_t) + capacity_in_bytes;
    circ_buff_t *new_circ_buff = malloc(size);
    if (!new_circ_buff)
    {
        return NULL;
    }

    memset(new_circ_buff, 0, size);

    /* initialise members */
    new_circ_buff->actual_capacity = capacity_in_bytes + 1;
    new_circ_buff->read_idx = 0;
    new_circ_buff->write_idx = 0;

    return new_circ_buff;
}

void CircBuffDestroy(circ_buff_t *circ_buff)
{
    if (!circ_buff)
    {
        return;
    }

    memset(circ_buff, 0, sizeof(circ_buff_t) + circ_buff->actual_capacity);
    free(circ_buff);
    circ_buff = NULL;
}

int CircBuffIsEmpty(const circ_buff_t *circ_buff)
{
    assert(circ_buff);

    return (circ_buff->read_idx == circ_buff->write_idx);
}

size_t CircBuffCapacity(const circ_buff_t *circ_buff)
{
    assert(circ_buff);

    return circ_buff->actual_capacity - 1;
}

size_t CircBuffFreeSpaceLeft(const circ_buff_t *circ_buff)
{
    assert(circ_buff);

    size_t read = circ_buff->read_idx;
    size_t write = circ_buff->write_idx;
    size_t capacity = circ_buff->actual_capacity;

    return ((capacity - 1 + read - write) % capacity);
}

ssize_t CircBuffGet(circ_buff_t *circ_buff, void *dest, size_t n_bytes)
{
    assert(circ_buff);
    assert(dest);

        return 0;
}

ssize_t CircBufPut(circ_buff_t *circ_buff, const void *src, size_t count)
{
    return 0;
}

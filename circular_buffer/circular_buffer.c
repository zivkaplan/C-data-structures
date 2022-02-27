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

typedef enum buff_state
{
    READ,
    WRITE
} buff_state_t;

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

static size_t Min(size_t a, size_t b);
static size_t MinOf3(size_t a, size_t b, size_t c);
static size_t SpacesToArrLastIndex(const circ_buff_t *circ_buff, buff_state_t state);

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

size_t CircBuffRead(circ_buff_t *circ_buff, void *dest, size_t n_bytes)
{
    assert(circ_buff);
    assert(dest);

    size_t total_read = 0;
    size_t available_to_read = CircBuffCapacity(circ_buff) - CircBuffFreeSpaceLeft(circ_buff);
    size_t first_operation_count = MinOf3(
        available_to_read,
        SpacesToArrLastIndex(circ_buff, READ),
        n_bytes);

    memcpy(dest, circ_buff->arr + circ_buff->read_idx, first_operation_count);

    circ_buff->read_idx += first_operation_count % circ_buff->actual_capacity;
    total_read += first_operation_count;
    dest = (char *)dest + first_operation_count;

    size_t available_to_read_left = CircBuffCapacity(circ_buff) -
                                    CircBuffFreeSpaceLeft(circ_buff);
    size_t left_to_read = Min(available_to_read_left, n_bytes - first_operation_count);
    memcpy(dest, circ_buff->arr + circ_buff->read_idx, left_to_read);

    circ_buff->read_idx += (left_to_read % circ_buff->actual_capacity);
    total_read += left_to_read;

    return total_read;
}

size_t CircBuffWrite(circ_buff_t *circ_buff, const void *src, size_t n_bytes)
{
    assert(circ_buff);
    assert(src);

    size_t free_spaces_left = CircBuffFreeSpaceLeft(circ_buff);

    size_t total_written = 0;
    size_t first_operation_count = MinOf3(
        free_spaces_left,
        SpacesToArrLastIndex(circ_buff, WRITE),
        n_bytes);

    memcpy(circ_buff->arr + circ_buff->write_idx, src, first_operation_count);

    circ_buff->write_idx += (first_operation_count % circ_buff->actual_capacity);
    total_written += first_operation_count;
    src = (char *)src + first_operation_count;
    size_t left_to_write = Min(CircBuffFreeSpaceLeft(circ_buff),
                               n_bytes - first_operation_count);

    memcpy(circ_buff->arr + circ_buff->write_idx, src, left_to_write);

    circ_buff->write_idx += (left_to_write % circ_buff->actual_capacity);
    total_written += left_to_write;

    return total_written;
}

static size_t MinOf3(size_t a, size_t b, size_t c)
{
    size_t temp_min = (a < b ? a : b);
    return (temp_min < c ? temp_min : c);
}

static size_t Min(size_t a, size_t b)
{
    return (a < b ? a : b);
}

static size_t SpacesToArrLastIndex(const circ_buff_t *circ_buff, buff_state_t state)
{
    assert(circ_buff);

    size_t current_idx = 0;

    switch (state)
    {
    case READ:
        current_idx = circ_buff->read_idx;
        break;

    case WRITE:
        current_idx = circ_buff->write_idx;
        break;
    }

    return circ_buff->actual_capacity - current_idx;
}
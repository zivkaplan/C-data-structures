#ifndef __ZK_VECTOR_H__
#define __ZK_VECTOR_H__

#include <stddef.h> /* size_t */

/***********************************
 * Dynamic Vector Data Structure
 * ------------------------
 *      Implementation in C
 *      elements are stored By value.
 *
 * Ziv Kaplan
 * February 2022
 **********************************/

typedef struct vector vector_t;

/*
Returns NULL on failure.
num_elements == 0 || size_element == 0 || growth_factor < 2  is undefined.
*/
vector_t *VectorCreate(size_t num_of_elements,
                       size_t element_size, size_t growth_factor);

/* Calling Destroy(NULL) is valid */
void VectorDestroy(vector_t *vector);

/* Calling Pop() on an empty vector is undefined */
void VectorPop(vector_t *vector);

/* On success returns 0, otherwise returns 1 */
int VectorPush(vector_t *vector, const void *val);

/*
calling AccessElement() with index that is equal or bigger than the size is undefined.
The returned pointer to the data is is valid until the next call to push()
*/
void *VectorAccessElement(vector_t *vector, size_t index);

size_t VectorGetCapacity(const vector_t *vector);

size_t VectorGetSize(const vector_t *vector);

int VectorIsEmpty(const vector_t *vector);

/* On success returns 0, otherwise returns 1 */
int VectorResize(vector_t *vector, size_t desired_num_of_elements);

/* On success returns 0, otherwise returns 1 */
int VectorShrinkToFit(vector_t *vector);

#endif /* __ZK_VECTOR_H__ */
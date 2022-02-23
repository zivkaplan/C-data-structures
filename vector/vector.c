/*********************************************************
 * Dynamic Vector Data Structure
 * -------------------------------------------------------
 *      Implementation in C
 *      Elements are stored By value.
 *
 * Ziv Kaplan
 * February 2022
 * -------------------------------------------------------
 * Please refer to the header file for the complete API.
 ********************************************************/

#include <stdlib.h> /* malloc(), free(), EXIT_SUCCESS, EXIT_FAILURE */
#include <string.h> /* memset() */
#include <assert.h> /* assert() */

#include "vector.h" /* header of the current source file */

/*********************************
 * Data Types
 ********************************/
struct vector
{
    size_t size;
    size_t capacity;
    size_t element_size;
    size_t growth_factor;
    void *arr;
};

/*********************************
 * Static Functions Declarations
 ********************************/
static size_t GetElementSize(const vector_t *vector);

/*********************************
 * API Functions Definitions
 ********************************/
vector_t *VectorCreate(size_t num_of_elements,
                       size_t element_size, size_t growth_factor)
{
    assert(num_of_elements != 0);
    assert(element_size != 0);
    assert(growth_factor > 2);

    vector_t *new_vector = malloc(sizeof(vector_t));
    void *arr = malloc(num_of_elements * element_size);
    if (!new_vector || !arr)
    {
        free(new_vector);
        free(arr);

        new_vector = NULL;
        arr = NULL;
        return NULL;
    }

    memset(new_vector, 0, sizeof(vector_t));
    memset(arr, 0, num_of_elements * element_size);

    /* Initialize members */
    new_vector->size = 0;
    new_vector->element_size = element_size;
    new_vector->capacity = num_of_elements;
    new_vector->growth_factor = growth_factor;
    new_vector->arr = arr;

    return new_vector;
}

void VectorDestroy(vector_t *vector)
{
    if (!vector)
    {
        return;
    }

    memset(vector->arr, 0, (VectorCapacity(vector) * GetElementSize(vector)));
    memset(vector, 0, sizeof(vector_t));

    free(vector);
    vector = NULL;
}

void VectorPop(vector_t *vector)
{
    assert(vector);

    vector->size--;
}

int VectorPush(vector_t *vector, const void *val)
{
    assert(vector);

    if (vector->size == vector->capacity)
    {
        if (VectorResize(vector, vector->capacity * vector->growth_factor))
        {
            return EXIT_FAILURE;
        }
    }
}

void *VectorAccessElement(vector_t *vector, size_t index)
{
    assert(vector);

    return (char *)vector + (index * vector->element_size);
}

size_t VectorCapacity(const vector_t *vector)
{
    assert(vector);

    return vector->capacity;
}

size_t VectorSize(const vector_t *vector)
{
    assert(vector);

    return vector->size;
}

int VectorIsEmpty(const vector_t *vector)
{
    assert(vector);

    return (0 == vector->size);
}

int VectorResize(vector_t *vector, size_t desired_num_of_elements)
{
    assert(vector);

    vector_t *new_address = realloc(vector->arr,
                                     desired_num_of_elements * GetElementSize(vector)));
    if (!new_address)
    {
        return EXIT_FAILURE;
    }

    memset(new_address, 0, desired_num_of_elements * GetElementSize(vector));

    /* update members */
    vector->arr = new_address;
    vector->capacity = desired_num_of_elements;

    return EXIT_SUCCESS;
}

int VectorShrinkToFit(vector_t *vector)
{
    assert(vector);

    return VectorResize(vector, VectorSize(vector));
}

/*********************************
 * Static Functions Definitions
 *********************************/
static size_t GetElementSize(const vector_t *vector)
{
    assert(vector);

    return vector->element_size;
}
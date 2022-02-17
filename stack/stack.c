/*********************************************************
 * Stack Data Structure
 * -------------------------------------------------------
 *      Implementation in C
 *      elements are stored By reference.
 *
 * Ziv Kaplan
 * February 2022
 * -------------------------------------------------------
 * Please read the header file for the complete API.
 ********************************************************/

#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* memset() */
#include <assert.h> /* assert() */

#include "stack.h" /* head of this source file */

struct stack
{
    size_t capacity;
    size_t current_size;
    void *data_arr[1];
};

static size_t GetStackStructSize(size_t capacity);

stack_t *CreateStack(size_t capacity)
{
    assert(capacity);

    stack_t *new_stack = malloc(GetStackStructSize(capacity));
    if (!new_stack)
    {
        return NULL;
    }

    memset(new_stack, 0, GetStackStructSize(capacity));
    new_stack->current_size = 0;
    new_stack->capacity = capacity;

    return new_stack;
}

void DestroyStack(stack_t *stack)
{
    if (!stack)
    {
        return;
    }

    memset(stack, 0, GetStackStructSize(stack->capacity));
    free(stack);
    stack = NULL;
}

void Pop(stack_t *stack)
{
    assert(stack);

    stack->current_size--;
}

void Push(stack_t *stack, void *pointer_to_element)
{
    assert(stack);

    stack->data_arr[stack->current_size] = pointer_to_element;
    stack->current_size++;
}

void *Peek(stack_t *stack)
{
    assert(stack);

    return stack->data_arr[stack->current_size - 1];
}

size_t GetSize(const stack_t *stack)
{
    assert(stack);

    return stack->current_size;
}

int IsStackEmpty(const stack_t *stack)
{
    assert(stack);

    return (0 == stack->current_size);
}

size_t GetCapacity(const stack_t *stack)
{
    assert(stack);
    return stack->capacity;
}

static size_t GetStackStructSize(size_t capacity)
{
    return (sizeof(stack_t) + (sizeof(void *) * (capacity - 1)));
    /* capacity - 1 since one element is already considered inside the stack struct */
}

#ifndef __ZK_STACK_H__
#define __ZK_STACK_H__

/***********************************
 * Stack Data Structure
 * ------------------------
 *      Implementation in C
 *      elements are stored By reference.
 *
 * Ziv Kaplan
 * February 2022
 **********************************/

#include <stddef.h> /* size_t */

typedef struct stack stack_t;

/* Returns NULL on failure */
stack_t *StackCreate(size_t capacity);

/* Calling DestroyStack(NULL) is valid */
void StackDestroy(stack_t *stack);

/* Calling Push() to a full stack is undefined behavior */
void StackPush(stack_t *stack, void *pointer_to_element);

/* Calling Pop() on an empty stack is undefined behavior */
void StackPop(stack_t *stack);

/* Calling Peek() on an empty stack is undefined behavior */
void *StackPeek(stack_t *stack);

size_t StackGetSize(const stack_t *stack);

int StackIsEmpty(const stack_t *stack);

size_t StackGetCapacity(const stack_t *stack);

#endif /* __ZK_STACK_H__ */

#ifndef __STACK_H__
#define __STACK_H__

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

stack_t *CreateStack(size_t capacity);
/* Returns NULL on failure */

void DestroyStack(stack_t *stack);
/* Calling DestroyStack(NULL) is valid */

void Push(stack_t *stack, void *pointer_to_element);
/* Calling Push() to a full stack is undefined behavior  */

void Pop(stack_t *stack);
/* Calling Pop() on an empty stack is undefined behavior  */

void *Peek(stack_t *stack);

size_t GetSize(const stack_t *stack);

int IsStackEmpty(const stack_t *stack);

size_t GetCapacity(const stack_t *stack);

#endif /* __TACK_H__ */

#ifndef __SINGLY_LINKED_LIST_H__
#define __SINGLY_LINKED_LIST_H__

#include <stddef.h> /* size_t */

/***********************************
 * Singly Linked List Data Structure
 * ------------------------
 *      Implementation in C
 *      elements are stored By reference.
 *
 * Ziv Kaplan
 * February 2022
 **********************************/

typedef struct list list_t;
typedef struct node *iter_t;

list_t *CreateList(void);
/*
returns NULL on failure.
*/

void DestroyList(list_t *list);
/* Calling DestroyList(NULL) is valid */

iter_t Insert(list_t list, iter_t iter, const void *data);
iter_t InsertAfter(list_t list, iter_t iter, const void *data);
/* returns the new inserted data on success, or list end on failure.
Insert(ListBegin) is undefined.
InsertAfter(ListEnd) is undefined.
To insert the first element use Insert(ListEnd) or InsertAfter(ListBegin).
*/

iter_t Remove(list_t list, iter_t iter);
iter_t RemoveAfter(list_t list, iter_t iter);
/*
return value is the next iterator.
Removing ListEnd is undefined.
*/

void *GetData(const iter_t iter);
void SetData(iter_t iter, const void *data);

iter_t ListBegin(const list_t *list);
iter_t ListEnd(const list_t *list);
iter_t ListNext(const iter_t iter);
int IsSameIterator(const iter_t iter1, const iter_t iter2);
/*
After any change in the list (inserting or removing data),
any existing iterators are invalidated and using them is undefined behaviour.
*/

iter_t ListFind(const list_t *list, void *param,
                int (*is_match_func)(const void *iterated_data, const void *param));
/*
returns ListEnd If No match found.
*/

iter_t ListForEach(list_t *list, void *param,
                   int (*oper_func)(void *iterated_data, void *param));
/*
iteration continue while oper_func returns 0.
returns ListEnd if iterated the entire list,
otherwise returns the iterator on which it was stopped.
*/

size_t ListGetSize(const list_t *list);
int ListIsEmpty(const list_t *list);

void SLListAppend(list_t *dest, list_t *src);
/* Concatenate src to the end of dest */

#endif /* __SINGLY_LINKED_LIST_H__ */

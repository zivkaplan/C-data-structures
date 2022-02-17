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

list_t *SinglyListCreate(void);
/*
returns NULL on failure.
*/

void SinglyListDestroy(list_t *list);
/* Calling DestroyList(NULL) is valid */

iter_t SinglyListInsert(list_t *list, iter_t iter, const void *data);
iter_t SinglyListInsertAfter(list_t *list, iter_t iter, const void *data);
/* returns the new inserted data on success, or list end on failure.
Insert(ListBegin) is undefined.
InsertAfter(ListEnd) is undefined.
To insert the first element use Insert(ListEnd) or InsertAfter(ListBegin).
*/

iter_t SinglyListRemove(list_t *list, iter_t iter);
/*
return value is the next iterator.
Removing ListEnd is undefined.
*/

void *SinglyListGetData(const iter_t iter);
void SinglyListSetData(iter_t iter, const void *data);

iter_t SinglyListBegin(const list_t *list);
iter_t SinglyListEnd(const list_t *list);
iter_t SinglyListNext(const iter_t iter);
int SinglyListIsSameIterator(const iter_t iter1, const iter_t iter2);
/*
After any change in the list (inserting or removing data),
any existing iterators are invalidated and using them is undefined behaviour.
*/

iter_t SinglyListFind(const list_t *list, void *param,
                      int (*is_match_func)(const void *iterated_data, const void *param));
/*
returns ListEnd If No match found.
*/

iter_t SinglyListForEach(list_t *list, void *param,
                         int (*oper_func)(void *iterated_data, void *param));
/*
iteration continue while oper_func returns 0.
returns ListEnd if iterated the entire list,
otherwise returns the iterator on which it was stopped.
*/

size_t SinglyListGetSize(const list_t *list);
int SinglyListIsEmpty(const list_t *list);

#endif /* __SINGLY_LINKED_LIST_H__ */

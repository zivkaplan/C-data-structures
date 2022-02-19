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

typedef struct singly_list singly_list_t;
typedef struct node *sll_iter_t;

singly_list_t *SinglyListCreate(void);
/* returns NULL on failure.*/

void SinglyListDestroy(singly_list_t *list);
/* Calling Destroy(NULL) is valid */

sll_iter_t SinglyListInsert(singly_list_t *list, sll_iter_t iter, const void *data);
sll_iter_t SinglyListInsertAfter(singly_list_t *list, sll_iter_t iter, const void *data);
/*
On success returns iterator to the new inserted data,
on failure returns ListEnd().
To insert the first element use only Insert(ListEnd).
InsertAfter(ListBegin) on an empty list is undefined.
InsertAfter(ListEnd) on any list is undefined.
*/

sll_iter_t SinglyListRemove(singly_list_t *list, sll_iter_t iter);
sll_iter_t SinglyListRemoveAfter(singly_list_t *list, sll_iter_t iter);
/*
Remove() returns the next iterator.
RemoveAfter() returns the previous iterator (meaning updated iterator from param).
Removing ListEnd is undefined.
Calling any Remove method on an empty list is undefined.
*/

void *SinglyListGetData(const sll_iter_t iter);
void SinglyListSetData(sll_iter_t iter, const void *data);
/*
Calling SetData/GetData on an empty list is undefined.
Calling SetData/GetData on ListEnd list is undefined.
*/

sll_iter_t SinglyListBegin(const singly_list_t *list);
sll_iter_t SinglyListEnd(const singly_list_t *list);
sll_iter_t SinglyListNext(const sll_iter_t iter);
int SinglyListIsSameIterator(const sll_iter_t iter1, const sll_iter_t iter2);
/*
After any change in the list (inserting or removing data),
any existing iterators are invalidated and using them is undefined behaviour.
*/

sll_iter_t SinglyListFind(const singly_list_t *list, void *param,
                          int (*is_match_func)(const void *iterated_data, const void *param));
/*
Returns the first matched iterator, or ListEnd if case no match found.
*/

sll_iter_t SinglyListForEach(singly_list_t *list, void *param,
                             int (*operation_func)(void *iterated_data, void *param));
/*
Iteration continues while operation_func returns 0.
Returns ListEnd if iterated through the entire list,
otherwise returns the iterator on which it was stopped.
*/

size_t SinglyListGetSize(const singly_list_t *list);
int SinglyListIsEmpty(const singly_list_t *list);

#endif /* __SINGLY_LINKED_LIST_H__ */

#ifndef __DOUBLY_LINKED_LIST_H__
#define __DOUBLY_LINKED_LIST_H__

#include <stddef.h> /* size_t */

/***********************************
 * Doubly Linked List Data Structure
 * ------------------------
 *      Implementation in C
 *      elements are stored By reference.
 *
 * Ziv Kaplan
 * February 2022
 **********************************/

typedef struct doubly_list doubly_list_t;
typedef struct dll_node *dll_iter_t;

doubly_list_t *DoublyListCreate(void);
/* returns NULL on failure.*/

void DoublyListDestroy(doubly_list_t *list);
/* Calling Destroy(NULL) is valid */

dll_iter_t DoublyListInsert(doubly_list_t list, dll_iter_t iter, const void *data);
/*
On success returns iterator to the new inserted data,
on failure returns ListEnd().
To insert the first element use only Insert(ListEnd).
*/

dll_iter_t DoublyListRemove(doubly_list_t list, dll_iter_t iter);
/*
Returns next iterator.
Removing ListEnd is undefined.
*/

size_t DoublyListSize(const doubly_list_t *list);
int DoublyListIsEmpty(const doubly_list_t *list);

void *DoublyListGetData(dll_iter_t iter);
void DoublyListSetData(dll_iter_t iter, const void *data);
/*
Calling SetData/GetData on an empty list is undefined.
Calling SetData/GetData on ListEnd list is undefined.
*/

dll_iter_t DoublyListBegin(const doubly_list_t *list);
dll_iter_t DoublyListEnd(const doubly_list_t *list);
dll_iter_t DoublyListNext(dll_iter_t iter);
dll_iter_t DoublyListPrev(dll_iter_t iter);
int DoublyListIsSameIterator(const dll_iter_t iter1, const dll_iter_t iter2);
/*
After any change in the list (inserting or removing data),
any existing iterators are invalidated and using them is undefined behaviour.
*/

dll_iter_t DoublyListFind(dll_iter_t from_iter, dll_iter_t to_iter,
                          void *param,
                          int (*is_match)(const void *data, const void *param));

/*
Returns the first matched iterator, or ListEnd if case no match found.
*/

int DoublyListFindAll(const doubly_list_t *list,
                      void *param,
                      int (*is_match)(const void *data, const void *param), doubly_list_t *output_list);

dll_iter_t DoublyListForEach(dll_iter_t from_iter, dll_iter_t to_iter,
                             void *param,
                             int (*operation_func)(void *data, void *param));
/*
Iteration continues while operation_func returns 0.
Returns ListEnd if iterated through the entire list,
otherwise returns the iterator on which it was stopped
*/

#endif /* __DOUBLY_LINKED_LIST_H__ */
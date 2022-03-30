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

/* returns NULL on failure.*/
doubly_list_t *DoublyListCreate(void);

/* Calling Destroy(NULL) is valid */
void DoublyListDestroy(doubly_list_t *list);

/*
On success returns iterator to the new inserted data,
on failure returns ListEnd().
To insert the first element use only Insert(ListEnd).
*/
dll_iter_t DoublyListInsert(doubly_list_t *list, dll_iter_t iter, const void *data);

/*
Returns next iterator.
Removing ListEnd is undefined.
*/
dll_iter_t DoublyListRemove(doubly_list_t *list, dll_iter_t iter);

size_t DoublyListGetSize(const doubly_list_t *list);
int DoublyListIsEmpty(const doubly_list_t *list);

/*
Calling GetData on an empty list is undefined.
Calling GetData on ListEnd list is undefined.
*/
void *DoublyListGetData(dll_iter_t iter);

/*
Calling SetData on an empty list is undefined.
Calling SetData on ListEnd list is undefined.
*/
void DoublyListSetData(dll_iter_t iter, const void *data);


/*
After any change in the list (inserting or removing data),
any existing iterators are invalidated and using them is undefined behaviour.
*/
dll_iter_t DoublyListBegin(const doubly_list_t *list);

/*
After any change in the list (inserting or removing data),
any existing iterators are invalidated and using them is undefined behaviour.
*/
dll_iter_t DoublyListEnd(const doubly_list_t *list);

/*
After any change in the list (inserting or removing data),
any existing iterators are invalidated and using them is undefined behaviour.
*/
dll_iter_t DoublyListNext(dll_iter_t iter);

/*
After any change in the list (inserting or removing data),
any existing iterators are invalidated and using them is undefined behaviour.
*/
dll_iter_t DoublyListPrev(dll_iter_t iter);

int DoublyListIsSameIterator(const dll_iter_t iter1, const dll_iter_t iter2);

/*
Returns the first matched iterator, or ListEnd if case no match found.
*/
dll_iter_t DoublyListFind(const doubly_list_t *list, void *param,
                          int (*is_match)(const void *data, const void *param));

/*
On success returns 0;
otherwise return 1.
found data is appended to the end of output_list.
In case of error mid-iteration, the data that was found until the error is appended.
*/
int DoublyListFindAll(const doubly_list_t *list,
                      void *param,
                      int (*is_match)(const void *data, const void *param), doubly_list_t *output_list);

/*
Iteration continues while operation_func returns 0.
Returns ListEnd if iterated through the entire list,
otherwise returns the iterator on which it was stopped
*/
dll_iter_t DoublyListForEach(doubly_list_t *list,
                             void *param,
                             int (*operation_func)(void *data, void *param));

#endif /* __DOUBLY_LINKED_LIST_H__ */
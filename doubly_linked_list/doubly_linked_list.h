#ifndef __DOUBLY_LINKED_LIST_H__
#define __DOUBLY_LINKED_LIST_H__

#include <stddef.h> /* size_t */

/**************************************************************
 * version 1.0                                                *
 *************************************************************/

typedef struct doubly_list doubly_list_t;
typedef struct node *dll_iter_t;

doubly_list_t *DoublyListCreate(void);
void DoublyListDestroy(doubly_list_t *list);

dll_iter_t DoublyListInsert(doubly_list_t list, dll_iter_t iter, void *data);
dll_iter_t DoublyListRemove(doubly_list_t list, dll_iter_t iter);

size_t DoublyListSize(const doubly_list_t *list);
int DoublyListIsEmpty(const doubly_list_t *list);

void *DoublyListGetData(dll_iter_t iter);
void *DoublyListSetData(dll_iter_t iter);

dll_iter_t DoublyListBegin(const doubly_list_t *list);
dll_iter_t DoublyListEnd(const doubly_list_t *list);
dll_iter_t DoublyListNext(dll_iter_t iter);
dll_iter_t DoublyListPrev(dll_iter_t iter);
int DoublyListIsSameIterator(const dll_iter_t iter1, const dll_iter_t iter2);

dll_iter_t DoublyListFind(dll_iter_t from_iter, dll_iter_t to_iter,
                          void *param,
                          int (*is_match)(const void *data, const void *param));
int DoublyListFindAll(const doubly_list_t *list,
                      void *param,
                      int (*is_match)(const void *data, const void *find_data), doubly_list_t *output_list);
int DoublyListForEach(dll_iter_t from_iter, dll_iter_t to_iter,
                      void *param,
                      int (*operation_func)(void *data, void *param));

#endif /* __DOUBLY_LINKED_LIST_H__ */
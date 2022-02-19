/*********************************************************
 * Doubly Linked List Data Structure
 * -------------------------------------------------------
 *      Implementation in C.
 *      Elements are stored By reference.
 *
 * Ziv Kaplan
 * February 2022
 * -------------------------------------------------------
 * Please refer to the header file for the complete API.
 ********************************************************/

#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* memset() */
#include <assert.h> /* assert() */

#include "doubly_linked_list.h" /* header of the current source file */

struct doubly_list
{
    struct dll_node *first;
    struct dll_node *last;
};

struct dll_node
{
    struct dll_node *next;
    struct dll_node *prev;
    void *data;
};

doubly_list_t *DoublyListCreate(void)
{
}

/*
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
                      int (*is_match)(const void *data, const void *param), doubly_list_t *output_list);

int DoublyListForEach(dll_iter_t from_iter, dll_iter_t to_iter,
                      void *param,
                      int (*operation_func)(void *data, void *param));
*/

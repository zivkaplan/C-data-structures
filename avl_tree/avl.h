#ifndef __ZK_AVL_H__
#define __ZK_AVL_H__

/***********************************
 * AVL tree
 * ------------------------
 *      Recursive implementation in C.
 *      Elements are stored By reference.
 *
 * Ziv Kaplan
 * February 2022
 **********************************/

#include <stddef.h> /* size_t */

typedef enum traverse_order
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER
} traverse_order_t;

typedef struct binary_search_tree avl_t;

/*
Returns NULL on failure.
is_before_func_t should return lhs < rhs.
*/
avl_t *AVLCreate(int (*is_before_func)(const void *lhs, const void *rhs));

/* Calling Destroy(NULL) is valid */
void AVLDestroy(avl_t *avl);

/*
Insert Unique values only.
Insretion of duplicated values results in an undefined behavior;
return 0 for success, otherwise return 1;
*/
int AVLInsert(avl_t *avl, void *data);

void AVLRemove(avl_t *avl, const void *data);
size_t AVLSize(const avl_t *avl);
size_t AVLHeight(const avl_t *avl);
int AVLIsEmpty(const avl_t *avl);

/*
Returns pointer to the data or NULL on case no match was found.
*/
void *AVLFind(const avl_t *avl, const void *data);

/*
Iteration continues while operation_func returns 0.
Returns ListEnd if iterated through the entire list,
otherwise returns the iterator on which it was stopped
*/
int AVLForEach(avl_t *avl, void *param, traverse_order_t order, int (*operation_func)(void *data, void *param));

#endif /* __ZK_AVL_H__ */

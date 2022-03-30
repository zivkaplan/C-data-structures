/*********************************************************
 * AVL tree
 * -------------------------------------------------------
 *      Recursive implementation in C.
 *      Elements are stored By reference.
 *
 * Ziv Kaplan
 * February 2022
 * -------------------------------------------------------
 * Please refer to the header file for the complete API.
 ********************************************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#ifdef DEBUG
#include <stdio.h> /* printf */
#endif

#include "avl.h" /* header of src file */

enum direction
{
    LEFT,
    RIGHT,
    NUM_OF_CHILDREN /* must be last */
};

enum exit_code
{
    SUCCESS,
    MALLOC_FAIL
};

enum balance_status
{
    BALANCED,
    NOT_BALANCED
};

typedef enum balance_status balance_status_t;
typedef enum exit_code exit_code_t;
typedef enum direction direction_t;
typedef struct node node_t;
typedef int (*is_before_func_t)(const void *lhs, const void *rhs);

struct binary_search_tree
{
    node_t *root;
    is_before_func_t is_before;
};

struct node
{
    void *data;
    node_t *children[NUM_OF_CHILDREN];
    size_t height;
};

/*********************************
 * static functions declarations
 *********************************/

/* recursive */
static node_t *RecursiveFind(node_t *node, const void *data, is_before_func_t is_before);
static node_t *RecursiveInsert(node_t *node, const void *data,
                               is_before_func_t is_before, exit_code_t *malloc_exit_code);
static node_t *RecursiveRemove(node_t *node, const void *data, is_before_func_t is_before);
static size_t RecursiveSize(const node_t *node);
static void RecursiveDestroy(node_t *node);
static int ForEachInOrder(node_t *node, int (*action)(void *data, void *param),
                          void *param, int res);
static int ForEachPostOrder(node_t *node, int (*action)(void *data, void *param),
                            void *param, int res);
static int ForEachPreOrder(node_t *node, int (*action)(void *data, void *param),
                           void *param, int res);

/* Gets */
static node_t *GetRoot(const avl_t *avl);
static node_t *GetChild(const node_t *node, direction_t side);
static int GetHeight(const node_t *node);
static int GetBalance(const node_t *node);
static void *GetData(const node_t *node);
static node_t *GetPrevious(node_t *node);
static size_t GetNumOfChilds(const node_t *node);

/* Sets */
static void SetRoot(avl_t *avl, node_t *node);
static void SetChild(node_t *parent, node_t *child, direction_t direction);
static void SetHeight(node_t *node, size_t num);
static void SetData(node_t *node, void *data);

/* height & balance */
static node_t *BalanceTree(node_t *node);
static node_t *Rotate(node_t *node, direction_t direction, balance_status_t balance_state);
static void UpdateHeightOnInsertion(node_t *node);
static void UpdateHeightOnDeletion(node_t *node);
static void UpdateHeightAfterBalance(node_t *node, node_t *child, balance_status_t balance_state);

/* utilities */
static node_t *HandleRemove(node_t *node, is_before_func_t is_before);
static int IsFound(const void *data_1, const void *data_2, is_before_func_t is_before);
static node_t *CreateNode(const void *data, exit_code_t *malloc_exit_code);

#ifdef DEBUG
static void PrintTree(const node_t *node);
#endif

/************************************************************************
 *                          External API Functions
 ***********************************************************************/

avl_t *AVLCreate(is_before_func_t is_before_func)
{
    assert(is_before_func);

    avl_t *new_avl = NULL;

    new_avl = malloc(sizeof(avl_t));
    if (!new_avl)
    {
        return NULL;
    }

    new_avl->is_before = is_before_func;
    new_avl->root = NULL;

    return new_avl;
}

void AVLDestroy(avl_t *avl)
{
    if (avl)
    {
        if (!AVLIsEmpty(avl))
        {
            RecursiveDestroy(avl->root);
        }
    }

    free(avl);
    avl = NULL;
}

int AVLInsert(avl_t *avl, void *data)
{
    assert(avl);

    exit_code_t malloc_exit_code = SUCCESS;
    node_t *node = NULL;

    node = RecursiveInsert(GetRoot(avl),
                           data, avl->is_before, &malloc_exit_code);

    SetRoot(avl, node);

    return malloc_exit_code;
}

void AVLRemove(avl_t *avl, const void *data)
{
    node_t *node = NULL;

    assert(avl);
    assert(avl->is_before);
    node = RecursiveRemove(GetRoot(avl), data, avl->is_before);

    SetRoot(avl, node);
}

int AVLIsEmpty(const avl_t *avl)
{
    assert(avl);

    return NULL == GetRoot(avl);
}

size_t AVLHeight(const avl_t *avl)
{
    assert(avl);

    return GetHeight(GetRoot(avl));
}

void *AVLFind(const avl_t *avl, const void *data)
{
    node_t *node = NULL;

    assert(avl);
    assert(avl->is_before);

    node = RecursiveFind(GetRoot(avl), data, avl->is_before);

    return (NULL == node ? NULL : GetData(node));
}

int AVLForEach(avl_t *avl, void *param, traverse_order_t order,
               int (*operation_func)(void *data, void *param))
{
    assert(avl);
    assert(operation_func);

    int res = 0;

    switch (order)
    {
    case PRE_ORDER:
        return ForEachPreOrder(GetRoot(avl), operation_func, param, res);

    case POST_ORDER:
        return ForEachPostOrder(GetRoot(avl), operation_func, param, res);

    default: /* case IN_ORDER */
        return ForEachInOrder(GetRoot(avl), operation_func, param, res);
    }
}

size_t AVLSize(const avl_t *avl)
{
    assert(avl);

    return RecursiveSize(GetRoot(avl));
}

/*************************************************************************
 *                       Static Functions
 *************************************************************************
 *                           Recursive
 *************************************************************************/

static void RecursiveDestroy(node_t *node)
{
    if (NULL == node)
    {
        return;
    }

    RecursiveDestroy(GetChild(node, LEFT));
    RecursiveDestroy(GetChild(node, RIGHT));

    free(node);
    node = NULL;
}

static node_t *RecursiveInsert(node_t *node, const void *data,
                               is_before_func_t is_before, exit_code_t *malloc_exit_code)
{
    direction_t direction = 0;
    node_t *child_node = 0;

    if (NULL == node)
    {
        return CreateNode(data, malloc_exit_code);
    }

    direction = is_before(GetData(node), data);

    child_node = RecursiveInsert(GetChild(node, direction), data,
                                 is_before, malloc_exit_code);

    SetChild(node, child_node, direction);

    if (SUCCESS == *malloc_exit_code)
    {
        UpdateHeightOnInsertion(node);

        return BalanceTree(node);
    }

    return node;
}

static node_t *RecursiveRemove(node_t *node, const void *data, is_before_func_t is_before)
{
    direction_t direction = 0;
    node_t *child = NULL;

    if (NULL == node)
    {
        return NULL;
    }

    direction = is_before(GetData(node), data);

    if (IsFound(GetData(node), data, is_before))
    {
        return HandleRemove(node, is_before);
    }

    child = RecursiveRemove(GetChild(node, direction), data, is_before);

    SetChild(node, child, direction);

    UpdateHeightOnDeletion(node);

    return BalanceTree(node);
}

static node_t *RecursiveFind(node_t *node, const void *data, is_before_func_t is_before)
{
    direction_t direction = 0;

    if (NULL == node)
    {
        return NULL;
    }

    direction = is_before(GetData(node), data);

    if (IsFound(GetData(node), data, is_before))
    {
        return node;
    }

    return RecursiveFind(GetChild(node, direction), data, is_before);
}

static size_t RecursiveSize(const node_t *node)
{
    size_t left_size = 0;
    size_t right_size = 0;

    if (NULL == node)
    {
        return 0;
    }

    left_size = RecursiveSize(GetChild(node, LEFT));
    right_size = RecursiveSize(GetChild(node, RIGHT));

    return left_size + right_size + 1;
}

static int ForEachPreOrder(node_t *node,
                           int (*action)(void *data, void *param),
                           void *param, int res)
{
    if (NULL == node)
    {
        return 0;
    }

    res = action(node->data, param);

    res = ForEachPreOrder(GetChild(node, LEFT), action, param, res);

    res = ForEachPreOrder(GetChild(node, RIGHT), action, param, res);

    return res;
}

static int ForEachInOrder(node_t *node,
                          int (*action)(void *data, void *param),
                          void *param, int res)
{
    if (NULL == node)
    {
        return 0;
    }

    res = ForEachInOrder(GetChild(node, LEFT), action, param, res);

    res = action(node->data, param);

    res = ForEachInOrder(GetChild(node, RIGHT), action, param, res);

    return res;
}

static int ForEachPostOrder(node_t *node,
                            int (*action)(void *data, void *param),
                            void *param, int res)
{
    if (NULL == node)
    {
        return 0;
    }

    res = ForEachPostOrder(GetChild(node, LEFT), action, param, res);

    res = ForEachPostOrder(GetChild(node, RIGHT), action, param, res);

    res = action(node->data, param);

    return res;
}

/************************************************************************
 *                          Gets
 ***********************************************************************/

static node_t *GetPrevious(node_t *node)
{
    assert(node);

    node = GetChild(node, LEFT);

    while (GetChild(node, RIGHT))
    {
        node = GetChild(node, RIGHT);
    }

    return node;
}

static void *GetData(const node_t *node)
{
    assert(node);

    return node->data;
}

static int GetHeight(const node_t *node)
{
    if (NULL == node)
    {
        return -1;
    }

    return node->height;
}

static node_t *GetChild(const node_t *node, direction_t side)
{
    assert(node);

    return node->children[side];
}

static node_t *GetRoot(const avl_t *avl)
{
    assert(avl);

    return avl->root;
}

static size_t GetNumOfChilds(const node_t *node)
{
    size_t counter = 0;

    if (GetChild(node, LEFT))
    {
        counter++;
    }

    if (GetChild(node, RIGHT))
    {
        counter++;
    }

    return counter;
}

static int GetBalance(const node_t *node)
{
    return GetHeight(GetChild(node, RIGHT)) -
           GetHeight(GetChild(node, LEFT));
}

/************************************************************************
 *                          Sets
 ***********************************************************************/

static void SetHeight(node_t *node, size_t num)
{
    assert(node);

    node->height = num;
}

static void SetRoot(avl_t *avl, node_t *node)
{
    assert(avl);

    avl->root = node;
}

static void SetChild(node_t *parent, node_t *child, direction_t direction)
{
    assert(parent);

    parent->children[direction] = child;
}

static void SetData(node_t *node, void *data)
{
    assert(node);

    node->data = data;
}

/************************************************************************
 *                          Height & Balance
 ***********************************************************************/

static void UpdateHeightAfterBalance(node_t *node, node_t *child, balance_status_t balance_state)
{
    size_t node_height = GetHeight(node);

    switch (balance_state)
    {
    case BALANCED:
        SetHeight(node, GetHeight(child) - 1);
        break;

    case NOT_BALANCED:
        SetHeight(child, node_height);
        SetHeight(node, node_height - 1);
        break;
    }
}
static void UpdateHeightOnInsertion(node_t *node)
{
    int node_height = GetHeight(node);

    if (node_height == GetHeight(GetChild(node, LEFT)) ||
        node_height == GetHeight(GetChild(node, RIGHT)))
    {
        SetHeight(node, (GetHeight(node) + 1));
    }
}

static void UpdateHeightOnDeletion(node_t *node)
{
    node_t *l_child = GetChild(node, LEFT);
    node_t *r_child = GetChild(node, RIGHT);

    size_t l_height = (NULL == l_child ? 0 : GetHeight(l_child));
    size_t r_height = (NULL == r_child ? 0 : GetHeight(r_child));
    size_t height_of_high_child = (l_height > r_height ? l_height : r_height);

    switch (GetNumOfChilds(node))
    {
    case 0:
        SetHeight(node, 0);
        return;

    default:
        SetHeight(node, height_of_high_child + 1);
        return;
    }
}

static node_t *BalanceTree(node_t *node)
{
    int balance = 0;

    assert(node);

    balance = GetBalance(node);

    /* left heavy  */
    if (-2 == balance)
    {
        /* left right */
        if (0 < GetBalance(GetChild(node, LEFT)))
        {
            node_t *child = Rotate(GetChild(node, LEFT), LEFT, NOT_BALANCED);
            SetChild(node, child, LEFT);
        }
        /* left left */
        node = Rotate(node, RIGHT, BALANCED);
    }

    /* right heavy */
    else if (2 == balance)
    {
        /* right left */
        if (0 > GetBalance(GetChild(node, RIGHT)))
        {
            node_t *child = Rotate(GetChild(node, RIGHT), RIGHT, NOT_BALANCED);
            SetChild(node, child, RIGHT);
        }
        /*  right right */
        node = Rotate(node, LEFT, BALANCED);
    }

    /* balanced */
    return node;
}

static node_t *Rotate(node_t *node, direction_t direction, balance_status_t balance_state)
{
    assert(node);
    {
        node_t *child = GetChild(node, !direction);

        SetChild(node, GetChild(child, direction), !direction);
        SetChild(child, node, direction);

        UpdateHeightAfterBalance(node, child, balance_state);

        return child;
    }
}

/************************************************************************
 *                          Utilities
 ***********************************************************************/

static node_t *CreateNode(const void *data, exit_code_t *malloc_exit_code)
{
    node_t *new_node = malloc(sizeof(node_t));

    if (NULL == new_node)
    {
        *malloc_exit_code = MALLOC_FAIL;
        return NULL;
    }

    new_node->data = (void *)data;
    new_node->height = 0;
    new_node->children[LEFT] = NULL;
    new_node->children[RIGHT] = NULL;

    return new_node;
}

static node_t *HandleRemove(node_t *node, is_before_func_t is_before)
{
    node_t *node_to_return = NULL;

    if (2 == GetNumOfChilds(node))
    {
        SetData(node, GetData(GetPrevious(node)));

        SetChild(node,
                 RecursiveRemove(
                     GetChild(node, LEFT), GetData(node), is_before),
                 LEFT);

        return BalanceTree(node);
    }

    node_to_return = (node_t *)((size_t)GetChild(node, LEFT) | (size_t)GetChild(node, RIGHT));

    free(node);
    node = NULL;

    return node_to_return;
}

static int IsFound(const void *data_1, const void *data_2, is_before_func_t is_before)
{
    assert(is_before);

    return (is_before(data_1, data_2) == is_before(data_2, data_1));
}

#ifdef DEBUG
static void PrintTree(const node_t *node)
{
    if (NULL == node)
    {
        printf("LEAF\n");
        return;
    }
    printf("data: %d\theight:%d\n", *(int *)GetData(node), GetHeight(node));

    PrintTree(GetChild(node, RIGHT));
    PrintTree(GetChild(node, LEFT));
}
#endif
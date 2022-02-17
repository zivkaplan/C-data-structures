#include <stdio.h> /* printf() */

#include "singly_linked_list.h" /* Create(), Destroy() */

#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BOLDWHITE "\033[1m\033[37m"
#define RESETCOLOR "\033[0m"

static const size_t NUM_OF_ELEMENTS_INSERT = 10;
static const size_t NUM_OF_ELEMENTS_INSERT_AFTER = 10;

typedef iter_t (*insert_func_t)(list_t *, iter_t, const void *);

void TestWithIntegers(void);

static iter_t AddElementAndTest(list_t *list, iter_t iter, insert_func_t insert_func, size_t value, size_t size);
static iter_t RemoveElementAndTest(list_t *list, iter_t iter, size_t value, size_t size);
static void PrintTest(size_t result, size_t expected, char *test_name, size_t line);

int main()
{
    TestWithIntegers();

    return 0;
}

void TestWithIntegers(void)
{
    size_t size = 0;
    list_t *list = CreateList();
    if (NULL == list)
    {
        printf(YELLOW "CreateStack returned NULL");
        return;
    }

    printf(BOLDWHITE "\nStack with integers (size_t variables):\n" RESETCOLOR);

    printf(BOLDWHITE "\nEmpty List\n" RESETCOLOR);

    PrintTest(ListIsEmpty(list), 1, "IsListEmpty", __LINE__);
    PrintTest(GetSize(list), size, "GetSize", __LINE__);

    iter_t iter = ListBegin(list);
    for (size_t i = 0; i < NUM_OF_ELEMENTS_INSERT; i++)
    {
        size++;
        iter = AddElementAndTest(list, iter, Insert, i, size);
    }

    for (size_t i = 0; i < NUM_OF_ELEMENTS_INSERT_AFTER; i++)
    {
        size++;
        iter = AddElementAndTest(list, iter, InsertAfter, i, size);
    }

    for (size_t i = NUM_OF_ELEMENTS_INSERT + NUM_OF_ELEMENTS_INSERT_AFTER;
         i > 0; i--)
    {
        size--;
        RemoveElementAndTest(list, iter, i - 1, size);
    }

    printf(BOLDWHITE "\nEmpty Stack\n" RESETCOLOR);

    PrintTest(ListIsEmpty(list), 1, "ListIsEmpty", __LINE__);
    PrintTest(GetSize(list), size, "GetSize", __LINE__);

    DestroyStack(list);

    printf(BOLDWHITE "\nTest finished.\n\n" RESETCOLOR);
}

static iter_t AddElementAndTest(list_t *list, iter_t iter,
                                insert_func_t insert_func,
                                size_t value, size_t size)
{
    printf(BOLDWHITE "\nAdding Element \n" RESETCOLOR);

    iter_t new_iter = insert_func(list, iter, (void *)value);

    PrintTest((size_t)Peek(list), value, "Peek", __LINE__);
    PrintTest(GetSize(list), size, "Size", __LINE__);
    PrintTest(ListIsEmpty(list), !size, "IsEmpty", __LINE__);

    return iter;
}

static iter_t RemoveElementAndTest(list_t *list, iter_t iter, size_t value, size_t size)
{
    printf(BOLDWHITE "\nRemoving Element \n" RESETCOLOR);

    PrintTest((size_t)Peek(list), value, "Peek", __LINE__);

    ListRemove(list);

    PrintTest(GetSize(list), size, "Size", __LINE__);
    PrintTest(ListIsEmpty(list), !size, "IsEmpty", __LINE__);
}

static void PrintTest(size_t result, size_t expected, char *test_name, size_t line)
{
    if (result == expected)
    {
        printf(GREEN "\t%s Passed\n" RESETCOLOR, test_name);
    }
    else
    {
        printf(RED "\t%s Failed. expected: %ld, result: %ld. (line %ld)\n" RESETCOLOR,
               test_name, expected, result, line);
    }
}

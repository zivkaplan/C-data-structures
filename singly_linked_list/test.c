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
    list_t *list = SinglyListCreate();
    if (NULL == list)
    {
        printf(YELLOW "SinglyListCreate returned NULL");
        return;
    }

    printf(BOLDWHITE "\nSinglyList with integers (size_t variables):\n" RESETCOLOR);

    printf(BOLDWHITE "\nEmpty List\n" RESETCOLOR);

    PrintTest(SinglyListIsEmpty(list), 1, "IsListEmpty", __LINE__);
    PrintTest(SinglyListGetSize(list), size, "SinglyListGetSize", __LINE__);

    iter_t iter = SinglyListBegin(list);
    for (size_t i = 0; i < NUM_OF_ELEMENTS_INSERT; i++)
    {
        size++;
        iter = AddElementAndTest(list, iter, SinglyListInsert, i, size);
    }

    for (size_t i = 0; i < NUM_OF_ELEMENTS_INSERT_AFTER; i++)
    {
        size++;
        iter = AddElementAndTest(list, iter, SinglyListInsertAfter, i, size);
    }

    for (size_t i = NUM_OF_ELEMENTS_INSERT + NUM_OF_ELEMENTS_INSERT_AFTER;
         i > 0; i--)
    {
        size--;
        RemoveElementAndTest(list, iter, i - 1, size);
    }

    printf(BOLDWHITE "\nEmpty Stack\n" RESETCOLOR);

    PrintTest(SinglyListIsEmpty(list), 1, "SinglyListIsEmpty", __LINE__);
    PrintTest(SinglyListGetSize(list), size, "SinglyListGetSize", __LINE__);

    SinglyListDestroy(list);

    printf(BOLDWHITE "\nTest finished.\n\n" RESETCOLOR);
}

static iter_t AddElementAndTest(list_t *list, iter_t iter,
                                insert_func_t insert_func,
                                size_t value, size_t size)
{
    printf(BOLDWHITE "\nAdding Element \n" RESETCOLOR);

    iter_t new_iter = insert_func(list, iter, (void *)value);

    PrintTest((size_t)SinglyListGetData(new_iter), value, "GetData", __LINE__);
    PrintTest(SinglyListGetSize(list), size, "Size", __LINE__);
    PrintTest(SinglyListIsEmpty(list), !size, "IsEmpty", __LINE__);

    return iter;
}

static iter_t RemoveElementAndTest(list_t *list, iter_t iter, size_t value, size_t size)
{
    printf(BOLDWHITE "\nRemoving Element \n" RESETCOLOR);

    PrintTest((size_t)SinglyListGetData(iter), value, "GetData", __LINE__);

    SinglyListRemove(list, iter);

    PrintTest(SinglyListGetSize(list), size, "Size", __LINE__);
    PrintTest(SinglyListIsEmpty(list), !size, "IsEmpty", __LINE__);
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

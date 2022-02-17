#include <stdio.h> /* printf() */

#include "singly_linked_list.h" /* Create(), Destroy(), Push(), Pop(), Peek(), 
                                GetSize(), GetCapacity(), IsEmpty() */

#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BOLDWHITE "\033[1m\033[37m"
#define RESETCOLOR "\033[0m"

typedef iter_t (*insert_func_t)(list_t *, iter_t, const void *);

void TestWithIntegers(void);

static void AddElementAndTest(list_t *list, iter_t iter, insert_func_t insert_func, size_t value, size_t size);
static void RemoveElementAndTest(list_t *list, iter_t iter, size_t value, size_t size);
static void PrintTest(size_t result, size_t expected, char *test_name, size_t line);

int main()
{
    TestWithIntegers();

    return 0;
}

void TestWithIntegers(void)
{
    size_t size = 0;

    list_t *list = CreateStack(stack_capacity);
    if (NULL == list)
    {
        printf(YELLOW "CreateStack returned NULL");
        return;
    }

    printf(BOLDWHITE "\nStack with integers (size_t variables):\n" RESETCOLOR);

    printf(BOLDWHITE "\nEmpty Stack\n" RESETCOLOR);

    PrintTest(IsStackEmpty(list), 1, "IsStackEmpty", __LINE__);
    PrintTest(GetCapacity(list), stack_capacity, "GetCapacity", __LINE__);
    PrintTest(GetSize(list), size, "GetSize", __LINE__);

    for (size_t i = 0; i < stack_capacity; i++)
    {
        size++;
        AddElementAndTest(list, i, size);
    }

    for (size_t i = stack_capacity; i > 0; i--)
    {
        size--;
        RemoveElementAndTest(list, i - 1, size);
    }

    printf(BOLDWHITE "\nEmpty Stack\n" RESETCOLOR);

    PrintTest(IsStackEmpty(list), 1, "IsStackEmpty", __LINE__);
    PrintTest(GetCapacity(list), stack_capacity, "GetCapacity", __LINE__);
    PrintTest(GetSize(list), size, "GetSize", __LINE__);

    DestroyStack(list);

    printf(BOLDWHITE "\nTest finished.\n\n" RESETCOLOR);
}

static void AddElementAndTest(list_t *list, iter_t iter,
                              insert_func_t insert_func,
                              size_t value, size_t size)
{
    printf(BOLDWHITE "\nAdding Element \n" RESETCOLOR);

    insert_func(list, iter, (void *)value);

    PrintTest((size_t)Peek(list), value, "Peek", __LINE__);
    PrintTest(GetSize(list), size, "Size", __LINE__);
    PrintTest(IsStackEmpty(list), !size, "IsEmpty", __LINE__);
}

static void RemoveElementAndTest(list_t *list, iter_t iter, size_t value, size_t size)
{
    printf(BOLDWHITE "\nRemoving Element \n" RESETCOLOR);

    PrintTest((size_t)Peek(list), value, "Peek", __LINE__);

    Pop(list);

    PrintTest(GetSize(list), size, "Size", __LINE__);
    PrintTest(IsStackEmpty(list), !size, "IsEmpty", __LINE__);
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

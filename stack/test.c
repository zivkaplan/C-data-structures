#include <stdio.h> /* printf() */

#include "stack.h" /* Create(), Destroy(), StackPush(), Pop(), StackPeek(), 
                      StackGetSize(), StackGetCapacity(), IsEmpty() */

#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BOLDWHITE "\033[1m\033[37m"
#define RESETCOLOR "\033[0m"

void TestWithIntegers(void);

static void AddElementAndTest(stack_t *stack, size_t value, size_t size);
static void RemoveElementAndTest(stack_t *stack, size_t value, size_t size);
static void PrintTest(size_t result, size_t expected, char *test_name, size_t line);

int main()
{
    TestWithIntegers();

    return 0;
}

void TestWithIntegers(void)
{
    const size_t stack_capacity = 5;
    size_t size = 0;

    stack_t *stack = StackCreate(stack_capacity);
    if (NULL == stack)
    {
        printf(YELLOW "StackCreate returned NULL");
        return;
    }

    printf(BOLDWHITE "\nStack with integers (size_t variables):\n" RESETCOLOR);

    printf(BOLDWHITE "\nEmpty Stack\n" RESETCOLOR);

    PrintTest(StackIsEmpty(stack), 1, "StackIsEmpty", __LINE__);
    PrintTest(StackGetCapacity(stack), stack_capacity, "StackGetCapacity", __LINE__);
    PrintTest(StackGetSize(stack), size, "StackGetSize", __LINE__);

    for (size_t i = 0; i < stack_capacity; i++)
    {
        size++;
        AddElementAndTest(stack, i, size);
    }

    for (size_t i = stack_capacity; i > 0; i--)
    {
        size--;
        RemoveElementAndTest(stack, i - 1, size);
    }

    printf(BOLDWHITE "\nEmpty Stack\n" RESETCOLOR);

    PrintTest(StackIsEmpty(stack), 1, "StackIsEmpty", __LINE__);
    PrintTest(StackGetCapacity(stack), stack_capacity, "StackGetCapacity", __LINE__);
    PrintTest(StackGetSize(stack), size, "StackGetSize", __LINE__);

    StackDestroy(stack);

    printf(BOLDWHITE "\nTest finished.\n\n" RESETCOLOR);
}

static void AddElementAndTest(stack_t *stack, size_t value, size_t size)
{
    printf(BOLDWHITE "\nAdding Element \n" RESETCOLOR);

    StackPush(stack, (void *)value);

    PrintTest((size_t)StackPeek(stack), value, "StackPeek", __LINE__);
    PrintTest(StackGetSize(stack), size, "Size", __LINE__);
    PrintTest(StackIsEmpty(stack), !size, "IsEmpty", __LINE__);
}

static void RemoveElementAndTest(stack_t *stack, size_t value, size_t size)
{
    printf(BOLDWHITE "\nRemoving Element \n" RESETCOLOR);

    PrintTest((size_t)StackPeek(stack), value, "StackPeek", __LINE__);

    StackPop(stack);

    PrintTest(StackGetSize(stack), size, "Size", __LINE__);
    PrintTest(StackIsEmpty(stack), !size, "IsEmpty", __LINE__);
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

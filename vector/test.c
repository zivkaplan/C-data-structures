#include <stdio.h> /* printf() */

#include "vector.h" /* Create(), Destroy(), VectorPush(), Pop(), VectorPeek(), 
                      VectorGetSize(), VectorGetCapacity(), IsEmpty() */

#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BOLDWHITE "\033[1m\033[37m"
#define RESETCOLOR "\033[0m"

typedef struct square
{
    size_t width;
    size_t height;

} square_t;

void RunTest(void);

static void AddElementAndTest(vector_t *vector, size_t value, size_t size);
static void RemoveElementAndTest(vector_t *vector, size_t value, size_t size);
static void PrintTest(size_t result, size_t expected, char *test_name, size_t line);

int main()
{
    RunTest();

    return 0;
}

void RunTest(void)
{
    size_t size = 0;
    size_t original_capacity = 3;

    size_t num_of_squares = 15;

    square_t square_arr[15] = {0};
    InitSqureArr();

    vector_t *vector = VectorCreate(original_capacity, sizeof(square_t), 2);
    if (NULL == vector)
    {
        printf(YELLOW "VectorCreate returned NULL");
        return;
    }

    printf(BOLDWHITE "\nVector with integers (size_t variables):\n" RESETCOLOR);

    printf(BOLDWHITE "\nEmpty Vector\n" RESETCOLOR);

    PrintTest(VectorIsEmpty(vector), 1, "VectorIsEmpty", __LINE__);
    PrintTest(VectorGetCapacity(vector), original_capacity, "VectorGetCapacity", __LINE__);
    PrintTest(VectorGetSize(vector), size, "VectorGetSize", __LINE__);

    for (size_t i = 0; i < num_of_squares; i++)
    {
        size++;
        AddElementAndTest(vector, , size);
    }

    for (size_t i = stack_capacity; i > 0; i--)
    {
        size--;
        RemoveElementAndTest(vector, i - 1, size);
    }

    printf(BOLDWHITE "\nEmpty Vector\n" RESETCOLOR);

    PrintTest(VectorIsEmpty(vector), 1, "VectorIsEmpty", __LINE__);
    PrintTest(VectorGetCapacity(vector), stack_capacity, "VectorGetCapacity", __LINE__);
    PrintTest(VectorGetSize(vector), size, "VectorGetSize", __LINE__);

    VectorDestroy(vector);

    printf(BOLDWHITE "\nTest finished.\n\n" RESETCOLOR);
}

static void AddElementAndTest(vector_t *vector, size_t value, size_t size)
{
    printf(BOLDWHITE "\nAdding Element \n" RESETCOLOR);

    VectorPush(vector, (void *)value);

    PrintTest((size_t)VectorPeek(vector), value, "VectorPeek", __LINE__);
    PrintTest(VectorGetSize(vector), size, "Size", __LINE__);
    PrintTest(VectorIsEmpty(vector), !size, "IsEmpty", __LINE__);
}

static void RemoveElementAndTest(vector_t *vector, size_t value, size_t size)
{
    printf(BOLDWHITE "\nRemoving Element \n" RESETCOLOR);

    PrintTest((size_t)VectorPeek(vector), value, "VectorPeek", __LINE__);

    VectorPop(vector);

    PrintTest(VectorGetSize(vector), size, "Size", __LINE__);
    PrintTest(VectorIsEmpty(vector), !size, "IsEmpty", __LINE__);
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

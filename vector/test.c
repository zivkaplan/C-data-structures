#include <stdio.h> /* printf() */

#include "vector.h" /* Create(), Destroy(), Push(), Pop(), AccessElement(), 
                      GetSize(), GetCapacity(), IsEmpty(), Resize(), ShrinkToFit() */

#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BOLDWHITE "\033[1m\033[37m"
#define RESETCOLOR "\033[0m"

#define ARR_SIZE 20

typedef struct square
{
    size_t width;
    size_t height;

} square_t;

static size_t passed_test_cases = 0;
static size_t failed_test_cases = 0;

void RunTest1(void);
void RunTest2(void);

static void AddElementAndTest(vector_t *vector, size_t value, size_t size);
static void RemoveElementAndTest(vector_t *vector, size_t value, size_t size);
static void PrintTest(size_t result, size_t expected, char *test_name, size_t line);
static void PrintResults(void);
static void InitSquaresArr(square_t *square_arr, size_t size);

int main()
{
    RunTest1();
    RunTest2();

    return 0;
}

void RunTest1(void)
{
    size_t size = 0;
    size_t original_capacity = 3;

    square_t square_arr[ARR_SIZE] = {0};
    InitSquaresArr(square_arr, ARR_SIZE);

    vector_t *vector = VectorCreate(original_capacity, sizeof(square_t), 2);
    if (NULL == vector)
    {
        printf(YELLOW "VectorCreate returned NULL");
        return;
    }

    PrintTest(VectorIsEmpty(vector), 1, "VectorIsEmpty", __LINE__);
    PrintTest(VectorGetCapacity(vector), original_capacity, "VectorGetCapacity", __LINE__);
    PrintTest(VectorGetSize(vector), size, "VectorGetSize", __LINE__);

    for (size_t i = 0; i < ARR_SIZE; i++)
    {
        size++;
        AddElementAndTest(vector, i, size);
    }

    for (size_t i = ARR_SIZE; i > 0; i--)
    {
        size--;
        RemoveElementAndTest(vector, i - 1, size);
    }

    PrintTest(VectorIsEmpty(vector), 1, "VectorIsEmpty", __LINE__);
    PrintTest(VectorGetSize(vector), size, "VectorGetSize", __LINE__);

    VectorDestroy(vector);

    PrintResults();
}

void RunTest2(void)
{
    size_t original_capacity = 1;
    size_t resized_capacity = 1;
    size_t loops = 10;
    size_t i = 0;

    vector_t *vector = VectorCreate(original_capacity, sizeof(void *), 2);
    if (NULL == vector)
    {
        printf(YELLOW "VectorCreate returned NULL");
        return;
    }

    VectorResize(vector, resized_capacity);
    PrintTest(VectorGetCapacity(vector), resized_capacity, "VectorGetCapacity", __LINE__);
    PrintTest(VectorGetCapacity(vector), resized_capacity, "VectorGetCapacity", __LINE__);

    for (i = 0; i < loops; i++)
    {
        void *ptr = NULL;
        VectorPush(vector, &ptr);
        PrintTest(VectorGetSize(vector), i + 1, "VectorGetSize", __LINE__);
    }

    VectorShrinkToFit(vector);
    PrintTest(
        VectorGetCapacity(vector) == VectorGetSize(vector) && VectorGetSize(vector) == loops,
        1, "VectorShrinkToFit", __LINE__);
}

static void AddElementAndTest(vector_t *vector, size_t value, size_t size)
{
    VectorPush(vector, (void *)value);

    PrintTest(*(size_t *)VectorAccessElement(vector, value), value, "VectorAccessElement", __LINE__);
    PrintTest(VectorGetSize(vector), size, "VectorGetSize", __LINE__);
}

static void RemoveElementAndTest(vector_t *vector, size_t value, size_t size)
{
    VectorPop(vector);

    PrintTest(*(size_t *)VectorAccessElement(vector, value), value, "VectorAccessElement", __LINE__);
    PrintTest(VectorGetSize(vector), size, "VectorGetSize", __LINE__);
}

static void InitSquaresArr(square_t *square_arr, size_t size)
{
    size_t i = 0;
    for (i = 0; i < size; i++)
    {
        square_arr->height = i;
        square_arr->width = i;

        square_arr++;
    }
}

static void PrintTest(size_t result, size_t expected, char *test_name, size_t line)
{
    if (result == expected)
    {
        passed_test_cases++;
    }
    else
    {
        failed_test_cases++;
        printf(RED "\t%s Failed. expected: %ld, result: %ld. (line %ld)\n" RESETCOLOR,
               test_name, expected, result, line);
    }
}

static void PrintResults(void)
{
    printf(BOLDWHITE "\nVector Testing:\n" RESETCOLOR);
    if (failed_test_cases)
    {
        printf(GREEN "\t%ld Tests Passed.\n" RESETCOLOR, passed_test_cases);
        printf(YELLOW "\t%ld Tests failed.\n" RESETCOLOR, failed_test_cases);
    }
    else
    {
        printf(GREEN "\tAll Tests Passed.\n" RESETCOLOR);
    }
}
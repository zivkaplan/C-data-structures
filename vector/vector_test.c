#include <stdio.h> /* printf () */
#include "vector.h"

void Red(void)
{
    printf("\033[1;31m");
}

void Green(void)
{
    printf("\033[1;32m");
}

void Reset(void)
{
    printf("\033[0m");
}

void PrintSucceeded(void)
{
    Green();
    printf("The Test Succeeded!!\n");
    Reset();
}

void PrintFailed(void)
{
    Red();
    printf("The Test Failed!!\n");
    Reset();
}

void IsExpectedEqualAns(int expected, int ans)
{
    if (expected == ans)
    {
        PrintSucceeded();
    }
    else
    {
        PrintFailed();
        printf("The ans is %d\n", ans);
    }
}

void TestVectorCreate(void)
{
    vector_t *vector = NULL;
    vector = VectorCreate(10, 4, 2);

    if (vector != NULL)
    {
        PrintSucceeded();
    }
    else
    {
        PrintFailed();
    }

    VectorDestroy(vector);
}

void TestVectorPopBack(void)
{
    vector_t *vector = VectorCreate(5, sizeof(int), 2);
    int num1 = 7;
    int num2 = 6;
    int num3 = 10;

    VectorPush(vector, &num1);
    VectorPush(vector, &num2);
    VectorPush(vector, &num3);
    VectorPop(vector);
    IsExpectedEqualAns(6, *(int *)(VectorAccessElement(vector, 1)));
    VectorPop(vector);
    IsExpectedEqualAns(7, *(int *)(VectorAccessElement(vector, 0)));
    VectorDestroy(vector);
}

void TestVectorPushBack(void)
{
    vector_t *vector = VectorCreate(5, sizeof(int), 2);
    int num1 = 2;
    int num2 = 10;
    int num3 = 8;

    VectorPush(vector, &num1);
    IsExpectedEqualAns(2, *(size_t *)(VectorAccessElement(vector, 0)));
    VectorPush(vector, &num2);
    IsExpectedEqualAns(10, *(size_t *)(VectorAccessElement(vector, 1)));
    VectorPush(vector, &num3);
    IsExpectedEqualAns(8, *(size_t *)(VectorAccessElement(vector, 2)));
    VectorDestroy(vector);
}

void TestVectorAccessElement(void)
{
    vector_t *vector = VectorCreate(200, sizeof(int), 2);
    int num1 = 7;
    int num2 = 6;
    int num3 = 8;

    VectorPush(vector, &num1);
    IsExpectedEqualAns(7, *(int *)(VectorAccessElement(vector, 0)));
    VectorPush(vector, &num2);
    IsExpectedEqualAns(6, *(int *)(VectorAccessElement(vector, 1)));

    VectorPop(vector);

    IsExpectedEqualAns(7, *(int *)(VectorAccessElement(vector, 0)));
    VectorPush(vector, &num3);
    IsExpectedEqualAns(8, *(int *)(VectorAccessElement(vector, 1)));

    VectorDestroy(vector);
    vector = NULL;
}

void TestVectorSize(void)
{
    vector_t *vector = VectorCreate(5, 4, 2);
    int num1 = 7;
    int num2 = 6;
    int num3 = 8;

    VectorPush(vector, &num1);
    IsExpectedEqualAns(1, VectorSize(vector));
    VectorPush(vector, &num2);
    IsExpectedEqualAns(2, VectorSize(vector));
    VectorPop(vector);
    IsExpectedEqualAns(1, VectorSize(vector));
    VectorPush(vector, &num2);
    VectorPush(vector, &num3);
    IsExpectedEqualAns(3, VectorSize(vector));
    VectorDestroy(vector);
}

void TestVectorIsEmpty(void)
{
    vector_t *vector = VectorCreate(5, 1, 2);
    int num1 = 7;
    int num2 = 6;
    int num3 = 10;

    IsExpectedEqualAns(1, VectorIsEmpty(vector));
    VectorPush(vector, &num1);
    VectorPush(vector, &num2);
    VectorPush(vector, &num3);
    IsExpectedEqualAns(0, VectorIsEmpty(vector));
    VectorDestroy(vector);
}

void TestVectorCapacity(void)
{
    vector_t *vector = VectorCreate(5, sizeof(int), 2);
    int num1 = 7;
    int num2 = 6;
    int num3 = 10;

    VectorPush(vector, &num1);
    VectorPush(vector, &num2);
    VectorPush(vector, &num3);
    IsExpectedEqualAns(5, VectorCapacity(vector));
    VectorDestroy(vector);

    vector = VectorCreate(1, sizeof(int), 2);
    IsExpectedEqualAns(1, VectorCapacity(vector));
    VectorDestroy(vector);
    vector = VectorCreate(50, sizeof(int), 2);
    VectorPush(vector, &num1);
    IsExpectedEqualAns(50, VectorCapacity(vector));
    VectorDestroy(vector);
}

void TestVectorReserve(void)
{
    vector_t *vector = VectorCreate(5, 4, 2);
    int num1 = 7;
    int num2 = 6;
    int num3 = 10;

    VectorPush(vector, &num1);
    VectorPush(vector, &num2);
    VectorPush(vector, &num3);

    VectorResize(vector, 8);
    IsExpectedEqualAns(8, VectorCapacity(vector));
    VectorResize(vector, 100);
    VectorPush(vector, &num1);
    IsExpectedEqualAns(100, VectorCapacity(vector));
    VectorResize(vector, 2);
    IsExpectedEqualAns(2, VectorCapacity(vector));

    VectorDestroy(vector);
}

void TestVectorShrinkToFit(void)
{
    vector_t *vector = VectorCreate(5, 4, 2);
    int num1 = 7;
    int num2 = 6;
    int num3 = 10;

    VectorPush(vector, &num1);
    VectorPush(vector, &num2);
    VectorPush(vector, &num3);
    VectorShrinkToFit(vector);
    IsExpectedEqualAns(3, VectorCapacity(vector));
    VectorResize(vector, 100);
    VectorPop(vector);
    VectorShrinkToFit(vector);
    IsExpectedEqualAns(2, VectorCapacity(vector));
    VectorPop(vector);
    VectorShrinkToFit(vector);
    IsExpectedEqualAns(1, VectorCapacity(vector));

    VectorDestroy(vector);
}

int main()
{
    printf("\n\n\t\t.....Testing VectorCreate.....\n\n\n");
    TestVectorCreate();

    printf("\n\n\t\t.....Testing VectorPop.....\n\n\n");
    TestVectorPopBack();

    printf("\n\n\t\t.....Testing VectorPush.....\n\n\n");
    TestVectorPushBack();

    printf("\n\n\t\t.....Testing VectorAccessElement.....\n\n\n");
    TestVectorAccessElement();

    printf("\n\n\t\t.....Testing VectorSize.....\n\n\n");
    TestVectorSize();

    printf("\n\n\t\t.....Testing VectorIsEmpty.....\n\n\n");
    TestVectorIsEmpty();

    printf("\n\n\t\t.....Testing VectorCapacity.....\n\n\n");
    TestVectorCapacity();

    printf("\n\n\t\t.....Testing VectorResize.....\n\n\n");
    TestVectorReserve();

    printf("\n\n\t\t.....Testing VectorShrinkToFit.....\n\n\n");
    TestVectorShrinkToFit();

    return 0;
}
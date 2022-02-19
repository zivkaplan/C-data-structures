#include <stdio.h> /* printf() */

#include "queue.h" /* Create(), Destroy(), IsEmpty(), GetSize(), 
                      Enqueue(), Dequeue(), Peek() */

#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BOLDWHITE "\033[1m\033[37m"
#define RESETCOLOR "\033[0m"

void RunTest(void);
static void PrintTest(size_t result, size_t expected, char *test_name, size_t line);

int main()
{
    RunTest();

    return 0;
}

void RunTest(void)
{
    /* Testing Enqueue, Dequeue, IsEmpty, Size, Peek */

    int a = 1, b = 2,
        c = 3, d = 4;

    queue_t *q1 = QueueCreate();

    printf(BOLDWHITE "CreateQueue\n" RESETCOLOR);
    PrintTest(QueueGetSize(q1), 0, "GetSize", __LINE__);
    PrintTest(QueueIsEmpty(q1), 1, "IsEmpty", __LINE__);

    QueueEnqueue(q1, &a);

    printf(BOLDWHITE "Enqueue\n" RESETCOLOR);
    PrintTest(QueueGetSize(q1), 1, "GetSize", __LINE__);
    PrintTest(QueueIsEmpty(q1), 0, "IsEmpty", __LINE__);
    PrintTest(*(int *)QueuePeek(q1), 1, "Peek", __LINE__);

    QueueEnqueue(q1, &b);

    printf(BOLDWHITE "Enqueue\n" RESETCOLOR);
    PrintTest(QueueGetSize(q1), 2, "GetSize", __LINE__);
    PrintTest(QueueIsEmpty(q1), 0, "IsEmpty", __LINE__);
    PrintTest(*(int *)QueuePeek(q1), 1, "Peek", __LINE__);

    QueueEnqueue(q1, &c);

    printf(BOLDWHITE "Enqueue\n" RESETCOLOR);
    PrintTest(QueueGetSize(q1), 3, "GetSize", __LINE__);
    PrintTest(QueueIsEmpty(q1), 0, "IsEmpty", __LINE__);
    PrintTest(*(int *)QueuePeek(q1), 1, "Peek", __LINE__);

    QueueEnqueue(q1, &d);

    printf(BOLDWHITE "Enqueue\n" RESETCOLOR);
    PrintTest(QueueGetSize(q1), 4, "GetSize", __LINE__);
    PrintTest(QueueIsEmpty(q1), 0, "IsEmpty", __LINE__);
    PrintTest(*(int *)QueuePeek(q1), 1, "Peek", __LINE__);

    QueueDequeue(q1);

    printf(BOLDWHITE "Dequeue\n" RESETCOLOR);
    PrintTest(QueueGetSize(q1), 3, "GetSize", __LINE__);
    PrintTest(QueueIsEmpty(q1), 0, "IsEmpty", __LINE__);
    PrintTest(*(int *)QueuePeek(q1), 2, "Peek", __LINE__);

    QueueDequeue(q1);

    printf(BOLDWHITE "Dequeue\n" RESETCOLOR);
    PrintTest(QueueGetSize(q1), 2, "GetSize", __LINE__);
    PrintTest(QueueIsEmpty(q1), 0, "IsEmpty", __LINE__);
    PrintTest(*(int *)QueuePeek(q1), 3, "Peek", __LINE__);

    QueueDequeue(q1);

    printf(BOLDWHITE "Dequeue\n" RESETCOLOR);
    PrintTest(QueueGetSize(q1), 1, "GetSize", __LINE__);
    PrintTest(QueueIsEmpty(q1), 0, "IsEmpty", __LINE__);
    PrintTest(*(int *)QueuePeek(q1), 4, "Peek", __LINE__);

    QueueDequeue(q1);

    printf(BOLDWHITE "Dequeue\n" RESETCOLOR);
    PrintTest(QueueGetSize(q1), 0, "GetSize", __LINE__);
    PrintTest(QueueIsEmpty(q1), 1, "IsEmpty", __LINE__);

    QueueDestroy(q1);
    q1 = NULL;
    printf(RESETCOLOR);
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

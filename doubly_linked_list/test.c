#include <stdio.h>  /* printf() */
#include <assert.h> /* assert() */

#include "doubly_linked_list.h" /* Create(), Destroy(), Insert(), Remove()                  
                                   GetSize(), IsEmpty(), IsSameIterator(),
                                   ForEach(), Find(), FindAll(), 
                                   Begin(), End(), Next(), Prev(),
                                   GetData(), SetData() */

#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BOLDWHITE "\033[1m\033[37m"
#define RESETCOLOR "\033[0m"

void RunTest(void);
void TestFindAll(void);
static void PrintTest(size_t result, size_t expected, char *test_name, size_t line);
void ClearList(doubly_list_t *list);

int main()
{

    RunTest();
    TestFindAll();

    return 0;
}

int PrintNode(void *el, __attribute__((unused)) void *none)
{
    printf(YELLOW "\t\tdata: %d\n" RESETCOLOR, *(int *)el);

    return 0;
}

int FindByVal(const void *el, const void *val)
{
    return (*(int *)el == (long)val);
}

void ClearList(doubly_list_t *list)
{
    while (!DoublyListIsEmpty(list))
    {
        DoublyListRemove(list, DoublyListBegin(list));
    }
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

void RunTest(void)
{
    int n0 = 0, n1 = 1,
        n2 = 2, n3 = 3,
        n4 = 4, n5 = 5;

    doubly_list_t *list = DoublyListCreate();
    dll_iter_t iter = NULL;
    dll_iter_t found_iter = NULL;

    printf(BOLDWHITE "\nDoubly Linked List Test\n\nBasic Functions\n\n" RESETCOLOR);

    printf(BOLDWHITE "\nNew Empty List\n" RESETCOLOR);

    PrintTest(DoublyListGetSize(list), 0, "Size", __LINE__);
    PrintTest(DoublyListIsEmpty(list), 1, "IsEmpty", __LINE__);

    printf(BOLDWHITE "\nAdding Element (1)\n" RESETCOLOR);
    iter = DoublyListInsert(list, DoublyListEnd(list), &n1);
    PrintTest(DoublyListGetSize(list), 1, "Size", __LINE__);
    PrintTest(DoublyListIsEmpty(list), 0, "IsEmpty", __LINE__);

    printf(BOLDWHITE "\nRemoving Element (1)\n" RESETCOLOR);
    iter = DoublyListRemove(list, iter);
    PrintTest(DoublyListGetSize(list), 0, "Size", __LINE__);
    PrintTest(DoublyListIsEmpty(list), 1, "IsEmpty", __LINE__);

    printf(BOLDWHITE "\nAdding Element (1)\n" RESETCOLOR);
    iter = DoublyListInsert(list, DoublyListEnd(list), &n1);
    PrintTest(DoublyListGetSize(list), 1, "Size", __LINE__);
    PrintTest(DoublyListIsEmpty(list), 0, "IsEmpty", __LINE__);

    printf(BOLDWHITE "\nAdding Element (2) to End\n" RESETCOLOR);
    iter = DoublyListInsert(list, DoublyListEnd(list), &n2);
    PrintTest(DoublyListGetSize(list), 2, "Size", __LINE__);
    PrintTest(DoublyListIsEmpty(list), 0, "IsEmpty", __LINE__);

    DoublyListForEach(list, NULL, PrintNode);

    printf(BOLDWHITE "\nAdding Element (0) to Begin\n" RESETCOLOR);
    iter = DoublyListInsert(list, DoublyListBegin(list), &n0);
    PrintTest(DoublyListGetSize(list), 3, "Size", __LINE__);
    PrintTest(DoublyListIsEmpty(list), 0, "IsEmpty", __LINE__);

    DoublyListForEach(list, NULL, PrintNode);

    printf(BOLDWHITE "\nGet Last added Element's data\n" RESETCOLOR);
    PrintTest(*(int *)DoublyListGetData(iter), n0, "GetData", __LINE__);
    printf(BOLDWHITE "\nChange it's value to 5\n" RESETCOLOR);
    DoublyListSetData(iter, &n5);
    PrintTest(*(int *)DoublyListGetData(iter), n5, "SetData", __LINE__);

    DoublyListForEach(list, NULL, PrintNode);

    printf(BOLDWHITE "\nAdding Element (4) to End\n" RESETCOLOR);
    iter = DoublyListInsert(list, DoublyListEnd(list), &n4);
    PrintTest(DoublyListGetSize(list), 4, "Size", __LINE__);
    PrintTest(DoublyListIsEmpty(list), 0, "IsEmpty", __LINE__);

    DoublyListForEach(list, NULL, PrintNode);

    printf(BOLDWHITE "\nAdding Element (3) to middle\n" RESETCOLOR);
    iter = DoublyListInsert(list, iter, &n3);
    PrintTest(DoublyListGetSize(list), 5, "Size", __LINE__);
    PrintTest(DoublyListIsEmpty(list), 0, "IsEmpty", __LINE__);

    DoublyListForEach(list, NULL, PrintNode);

    printf(BOLDWHITE "\nRemoving Element (0) from Begin\n" RESETCOLOR);
    iter = DoublyListRemove(list, DoublyListBegin(list));
    PrintTest(DoublyListGetSize(list), 4, "Size", __LINE__);
    PrintTest(DoublyListIsEmpty(list), 0, "IsEmpty", __LINE__);

    DoublyListForEach(list, NULL, PrintNode);

    printf(BOLDWHITE "\nRemoving Element (4) from End\n" RESETCOLOR);
    iter = DoublyListRemove(list, DoublyListPrev(DoublyListEnd(list)));
    PrintTest(DoublyListGetSize(list), 3, "Size", __LINE__);
    PrintTest(DoublyListIsEmpty(list), 0, "IsEmpty", __LINE__);

    DoublyListForEach(list, NULL, PrintNode);

    printf(BOLDWHITE "\nAdding Element (4) to middle\n" RESETCOLOR);
    iter = DoublyListPrev(iter);
    iter = DoublyListInsert(list, iter, &n4);
    PrintTest(DoublyListGetSize(list), 4, "Size", __LINE__);
    PrintTest(DoublyListIsEmpty(list), 0, "IsEmpty", __LINE__);

    DoublyListForEach(list, NULL, PrintNode);

    printf(BOLDWHITE "\nFind Last Inserted Element\n" RESETCOLOR);
    found_iter = DoublyListFind(list, (void *)(long)n4, FindByVal);
    PrintTest(DoublyListIsSameIterator(iter, found_iter), 1, "IsSameIterator", __LINE__);

    printf(BOLDWHITE "\nTest Find With Non-Existing Value\n" RESETCOLOR);
    found_iter = DoublyListFind(list, (void *)(long)100, FindByVal);
    PrintTest(DoublyListIsSameIterator(DoublyListEnd(list), found_iter), 1, "IsSameIterator", __LINE__);

    printf(BOLDWHITE "\nTest IsSameIterator With Non-Matching Iters\n" RESETCOLOR);
    PrintTest(DoublyListIsSameIterator(DoublyListBegin(list), DoublyListEnd(list)), 0, "IsSameIterator", __LINE__);

    DoublyListDestroy(list);
    list = NULL;
}

void TestFindAll(void)
{
    int a = 1, b = 2;

    doubly_list_t *list_1 = DoublyListCreate();
    doubly_list_t *list_2 = DoublyListCreate();

    printf(BOLDWHITE "\n\nDoubly Linked List Test FindAll\n" RESETCOLOR);

    DoublyListInsert(list_1, DoublyListEnd(list_1), &a);
    DoublyListInsert(list_1, DoublyListEnd(list_1), &a);
    DoublyListInsert(list_1, DoublyListEnd(list_1), &b);
    DoublyListInsert(list_1, DoublyListEnd(list_1), &a);

    PrintTest(DoublyListGetSize(list_1), 4, "Size", __LINE__);
    PrintTest(DoublyListIsEmpty(list_1), 0, "IsEmpty", __LINE__);

    DoublyListFindAll(list_1, (void *)(long)a, FindByVal, list_2);
    PrintTest(DoublyListGetSize(list_2), 3, "Size", __LINE__);
    PrintTest(DoublyListIsEmpty(list_2), 0, "IsEmpty", __LINE__);
    DoublyListForEach(list_2, NULL, PrintNode);

    DoublyListDestroy(list_1);
    DoublyListDestroy(list_2);

    list_1 = NULL;
    list_2 = NULL;
}
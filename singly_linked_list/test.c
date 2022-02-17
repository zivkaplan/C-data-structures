#include <stdlib.h> /* malloc(), free() */
#include <stdio.h>  /* printf() */
#include <assert.h> /* assert() */

#include "singly_linked_list.h"

#define RESETCOLOR "\033[0m"
#define MAGENTA "\033[35m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define BOLDWHITE "\033[37m\033[1m"

static int PrintNode(void *el, __attribute__((unused)) void *none);
static int FindNodeByVal(const void *el, const void *val);
void RunTest();

int main()
{
    RunTest();
    return 0;
}

void RunTest()
{
    int a = 1, b = 2, c = 3, d = 4;

    list_t *list = SinglyListCreate();
    sll_iter_t iter = SinglyListEnd(list);
    sll_iter_t found_iter = NULL;

    printf(BOLDWHITE "\nEmpty List\n" RESETCOLOR);

    /* check empty list */
    printf(BLUE "list size = %ld\n" RESETCOLOR, SinglyListGetSize(list));
    printf(YELLOW "is empty? %s\n" RESETCOLOR, SinglyListIsEmpty(list) ? "yes" : "no");

    /* add an item and then check size and is empty and foreach */
    printf(BOLDWHITE "\n1 Element\n" RESETCOLOR);
    iter = SinglyListInsert(list, iter, &a);
    printf(BLUE "list size = %ld\n" RESETCOLOR, SinglyListGetSize(list));
    printf(YELLOW "is empty? %s\n" RESETCOLOR, SinglyListIsEmpty(list) ? "yes" : "no");
    SinglyListForEach(list, NULL, PrintNode);

    /* add an item and then check size and is empty and foreach */
    printf(BOLDWHITE "\n2 Elements\n" RESETCOLOR);
    iter = SinglyListInsertAfter(list, iter, &c);
    printf(BLUE "list size = %ld\n" RESETCOLOR, SinglyListGetSize(list));
    printf(YELLOW "is empty? %s\n" RESETCOLOR, SinglyListIsEmpty(list) ? "yes" : "no");
    SinglyListForEach(list, NULL, PrintNode);

    /* add an item and then check size and is empty and foreach */
    printf(BOLDWHITE "\n3 Elements\n" RESETCOLOR);
    iter = SinglyListInsert(list, iter, &b);
    printf(YELLOW "is empty? %s\n" RESETCOLOR, SinglyListIsEmpty(list) ? "yes" : "no");
    printf(BLUE "list size = %ld\n" RESETCOLOR, SinglyListGetSize(list));
    SinglyListForEach(list, NULL, PrintNode);

    /* add an item and then check size and is empty and foreach */
    printf(BOLDWHITE "\n4 Elements\n" RESETCOLOR);
    iter = SinglyListInsert(list, SinglyListEnd(list), &d);
    printf(YELLOW "is empty? %s\n" RESETCOLOR, SinglyListIsEmpty(list) ? "yes" : "no");
    printf(BLUE "list size = %ld\n" RESETCOLOR, SinglyListGetSize(list));
    SinglyListForEach(list, NULL, PrintNode);

    /* search for item with value 4, print it, update it to 5 and print it again */
    printf(BOLDWHITE "\nFind Element and Change its Value\n" RESETCOLOR);
    found_iter = SinglyListFind(list, &c, FindNodeByVal);
    printf("found iter value is %d\n", *(int *)(SinglyListGetData(found_iter)));
    c = -1;
    SinglyListSetData(found_iter, &c);
    printf("found iter value changed to %d\n", *(int *)(SinglyListGetData(found_iter)));
    SinglyListForEach(list, NULL, PrintNode);

    /* remove the element after it (the last), and then check size and is empty and foreach */
    printf(BOLDWHITE "\n3 Elements\n" RESETCOLOR);
    iter = SinglyListRemoveAfter(list, found_iter);
    printf(BLUE "list size = %ld\n" RESETCOLOR, SinglyListGetSize(list));
    printf(YELLOW "is empty? %s\n" RESETCOLOR, SinglyListIsEmpty(list) ? "yes" : "no");
    SinglyListForEach(list, NULL, PrintNode);

    /* remove the first element, and then check size and is empty and foreach */
    printf(BOLDWHITE "\n2 Elements\n" RESETCOLOR);
    iter = SinglyListRemove(list, SinglyListBegin(list));
    printf(BLUE "list size = %ld\n" RESETCOLOR, SinglyListGetSize(list));
    printf(YELLOW "is empty? %s\n" RESETCOLOR, SinglyListIsEmpty(list) ? "yes" : "no");
    SinglyListForEach(list, NULL, PrintNode);

    /* remove the second (last in order element), and then check size and is empty and foreach */
    printf(BOLDWHITE "\n1 Element\n" RESETCOLOR);
    iter = SinglyListRemoveAfter(list, SinglyListBegin(list));
    printf(BLUE "list size = %ld\n" RESETCOLOR, SinglyListGetSize(list));
    printf(YELLOW "is empty? %s\n" RESETCOLOR, SinglyListIsEmpty(list) ? "yes" : "no");
    SinglyListForEach(list, NULL, PrintNode);

    /* remove the first and only element left, and then check size and is empty and foreach */
    printf(BOLDWHITE "\nEmpty\n" RESETCOLOR);
    printf(BLUE "list size = %ld\n" RESETCOLOR, SinglyListGetSize(list));
    printf(YELLOW "is empty? %s\n" RESETCOLOR, SinglyListIsEmpty(list) ? "yes" : "no");

    SinglyListDestroy(list);
    list = NULL;
}

static int PrintNode(void *el, __attribute__((unused)) void *none)
{
    printf(MAGENTA "\tdata: %d\n", *(int *)el);

    return 0;
}

static int FindNodeByVal(const void *el, const void *val)
{
    return (*(int *)el == *(int *)val);
}

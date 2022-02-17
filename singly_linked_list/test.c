#include <stdlib.h> /* malloc(), free() */
#include <stdio.h>  /* printf() */
#include <assert.h> /* assert() */

#include "singly_linked_list.h"

#define RESETCOLOR "\033[0m"
#define MAGENTA "\033[35m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define BOLDWHITE "\033[37m\033[1m"

int PrintNode(void *el, __attribute__((unused)) void *none)
{
    printf(MAGENTA "data: %d\n", *(int *)el);

    return 0;
}

int FindNodeByVal(const void *el, const void *val)
{
    return !(*(int *)el == *(int *)val);
}

void TestSLL()
{

    int a = 1, b = 2, c = 3, d = 4;

    list_t *my_list = CreateList();
    iter_t iter = ListEnd(my_list);
    iter_t found_iter = NULL;

    printf(BOLDWHITE "\nEmpty List\n" RESETCOLOR);

    /* check empty list */
    printf(BLUE "list size = %ld\n" RESETCOLOR, ListGetSize(my_list));
    printf(YELLOW "is empty = %s\n" RESETCOLOR, ListIsEmpty(my_list) ? "yes" : "no");

    /* add an item and then check size and is empty and foreach */
    printf(BOLDWHITE "\n1 Element\n" RESETCOLOR);
    iter = Insert(my_list, iter, &a);
    printf(BLUE "list size = %ld\n" RESETCOLOR, ListGetSize(my_list));
    printf(YELLOW "is empty = %s\n" RESETCOLOR, ListIsEmpty(my_list) ? "yes" : "no");
    ListForEach(my_list, NULL, PrintNode);

    /* add an item and then check size and is empty and foreach */
    printf(BOLDWHITE "\n2 Elements\n" RESETCOLOR);
    iter = InsertAfter(my_list, iter, &b);
    printf(YELLOW "is empty = %s\n" RESETCOLOR, ListIsEmpty(my_list) ? "yes" : "no");
    printf(BLUE "list size = %ld\n" RESETCOLOR, ListGetSize(my_list));
    ListForEach(my_list, NULL, PrintNode);

    /* add an item and then check size and is empty and foreach */
    printf(BOLDWHITE "\n3 Elements\n" RESETCOLOR);
    iter = Insert(my_list, iter, &c);
    printf(YELLOW "is empty = %s\n" RESETCOLOR, ListIsEmpty(my_list) ? "yes" : "no");
    printf(BLUE "list size = %ld\n" RESETCOLOR, ListGetSize(my_list));
    ListForEach(my_list, NULL, PrintNode);

    /* add an item and then check size and is empty and foreach */
    printf(BOLDWHITE "\n4 Elements\n" RESETCOLOR);
    iter = Insert(my_list, iter, &d);
    printf(YELLOW "is empty = %s\n" RESETCOLOR, ListIsEmpty(my_list) ? "yes" : "no");
    printf(BLUE "list size = %ld\n" RESETCOLOR, ListGetSize(my_list));
    ListForEach(my_list, NULL, PrintNode);

    /* search for item with value 4, print it, update it to 5 and print it again */
    printf(BOLDWHITE "\nFind Element and Change its Value\n" RESETCOLOR);
    found_iter = ListFind(my_list, &d, FindNodeByVal);
    printf("found iter value is %d\n", *(int *)(GetData(found_iter)));
    d++;
    SetData(found_iter, &d);
    printf("found iter value changed to %d\n", *(int *)(GetData(found_iter)));

    /* remove the element after it (the last), and then check size and is empty and foreach */
    printf(BOLDWHITE "\n3 Elements\n" RESETCOLOR);
    iter = Remove(my_list, found_iter);
    printf(YELLOW "is empty = %s\n" RESETCOLOR, ListIsEmpty(my_list) ? "yes" : "no");
    printf(BLUE "list size = %ld\n" RESETCOLOR, ListGetSize(my_list));
    ListForEach(my_list, NULL, PrintNode);

    /* remove the first element, and then check size and is empty and foreach */
    printf(BOLDWHITE "\n2 Elements\n" RESETCOLOR);
    iter = Remove(my_list, ListBegin(my_list));
    printf(YELLOW "is empty = %s\n" RESETCOLOR, ListIsEmpty(my_list) ? "yes" : "no");
    printf(BLUE "list size = %ld\n" RESETCOLOR, ListGetSize(my_list));
    ListForEach(my_list, NULL, PrintNode);

    /* remove the second (last in order element), and then check size and is empty and foreach */
    printf(BOLDWHITE "\n1 Element\n" RESETCOLOR);
    iter = Remove(my_list, ListBegin(my_list));
    printf(YELLOW "is empty = %s\n" RESETCOLOR, ListIsEmpty(my_list) ? "yes" : "no");
    printf(BLUE "list size = %ld\n" RESETCOLOR, ListGetSize(my_list));
    ListForEach(my_list, NULL, PrintNode);

    /* remove the first and only element left, and then check size and is empty and foreach */
    printf(BOLDWHITE "\nEmpty\n" RESETCOLOR);
    iter = Remove(my_list, ListBegin(my_list));
    printf(YELLOW "is empty = %s\n" RESETCOLOR, ListIsEmpty(my_list) ? "yes" : "no");
    printf(BLUE "list size = %ld\n" RESETCOLOR, ListGetSize(my_list));

    DestroyList(my_list);
    my_list = NULL;
}

int main()
{
    TestSLL();

    return 0;
}
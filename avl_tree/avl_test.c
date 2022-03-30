#include <time.h>   /* time() */
#include <stdio.h>  /* printf() */
#include <stdlib.h> /* printf() */
#include <string.h> /* strcmp() */
#include <assert.h> /* assert() */

#include "avl.h"

#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define CYAN "\033[36m"
#define BOLDWHITE "\033[1m\033[37m"
#define RESETCOLOR "\033[0m"

void TestRemove(void);
void TestCreateDestroyInsertIsEmptySize(void);
void PrintTest(size_t result, size_t expected, char *test_name, size_t line);
int SortNums(const void *el, const void *val);
int PrintIntNode(void *el, __attribute__((unused)) void *none);
void AddElementAndTest(avl_t *tree, int *num_p, size_t size);
void RemoveElementAndTest(avl_t *tree, int *num_p, size_t size);
void TestFind(avl_t *tree);
void ShowTree(void);

int main()
{
    printf(BOLDWHITE "\nRecursive Binary Tree Test\n\n" RESETCOLOR);
    TestCreateDestroyInsertIsEmptySize();
    TestRemove();

    return 0;
}

void AddElementAndTest(avl_t *tree, int *num_p, size_t size)
{
    printf(BOLDWHITE "\nAdding Element \n" RESETCOLOR);
    AVLInsert(tree, num_p);

    printf(CYAN "\nPRE_ORDER\n" RESETCOLOR);
    AVLForEach(tree, NULL, PRE_ORDER, PrintIntNode);
    printf(CYAN "\n" RESETCOLOR);

    printf(CYAN "\nIN_ORDER\n" RESETCOLOR);
    AVLForEach(tree, NULL, IN_ORDER, PrintIntNode);
    printf(CYAN "\n" RESETCOLOR);

    printf(CYAN "\nPOST_ORDER\n" RESETCOLOR);
    AVLForEach(tree, NULL, POST_ORDER, PrintIntNode);
    printf(CYAN "\n" RESETCOLOR);

    PrintTest(AVLSize(tree), size, "Size", __LINE__);
    PrintTest(AVLIsEmpty(tree), !size, "IsEmpty", __LINE__);
}

void RemoveElementAndTest(avl_t *tree, int *num_p, size_t size)
{
    printf(CYAN "\nRemoving Element \n" RESETCOLOR);
    AVLRemove(tree, num_p);
    size--;

    AVLForEach(tree, NULL, IN_ORDER, PrintIntNode);
    printf(CYAN "\n" RESETCOLOR);

    PrintTest(AVLSize(tree), size, "Size", __LINE__);
    PrintTest(AVLIsEmpty(tree), !size, "IsEmpty", __LINE__);
}

int SortNums(const void *el, const void *val)
{
    return (*(int *)el) < (*(int *)val);
}

int PrintIntNode(void *el, __attribute__((unused)) void *none)
{
    printf(YELLOW "%d_" RESETCOLOR, *(int *)el);

    return 0;
}

void PrintTest(size_t result, size_t expected, char *test_name, size_t line)
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

void TestCreateDestroyInsertIsEmptySize(void)
{
    int n0 = 0;
    int n1 = 1;
    int n2 = 2;
    int n3 = 3;
    int n4 = 4;
    int n5 = 5;
    int n6 = 6;
    int n7 = 7;
    int n8 = 8;
    int n9 = 9;
    int n10 = 10;

    int size = 0;

    avl_t *tree = AVLCreate(SortNums);

    printf(BOLDWHITE "\nNew Empty List\n" RESETCOLOR);
    PrintTest(AVLSize(tree), 0, "Size", __LINE__);
    PrintTest(AVLIsEmpty(tree), 1, "IsEmpty", __LINE__);

    AddElementAndTest(tree, &n5, ++size);
    AddElementAndTest(tree, &n1, ++size);
    AddElementAndTest(tree, &n9, ++size);
    AddElementAndTest(tree, &n4, ++size);
    AddElementAndTest(tree, &n7, ++size);
    AddElementAndTest(tree, &n3, ++size);
    AddElementAndTest(tree, &n8, ++size);
    AddElementAndTest(tree, &n0, ++size);
    AddElementAndTest(tree, &n10, ++size);
    AddElementAndTest(tree, &n2, ++size);
    AddElementAndTest(tree, &n6, ++size);

    ShowTree();
    TestFind(tree);

    AVLDestroy(tree);
    tree = NULL;
}

void TestFind(avl_t *tree)
{
    int i = 0;
    printf(BOLDWHITE "\nTest Find\n" RESETCOLOR);

    for (i = 0; i < 15; i++)
    {
        int *data = AVLFind(tree, &i);

        if (i < 11)
        {
            PrintTest(*(int *)data, i, "Find", __LINE__);
        }
        else
        {
            PrintTest(NULL == data, 1, "Find", __LINE__);
        }
    }

    printf(YELLOW "\nTest Find finished\n" RESETCOLOR);
}

void TestRemove(void)
{

    int i = 0;
    int j = 0;
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size_of_arr = (int)(sizeof(arr) / sizeof(arr[0]));

    avl_t *tree = AVLCreate(SortNums);

    srand(time(NULL));

    printf(BOLDWHITE "\nTest Remove\n\n\n" RESETCOLOR);

    /* check random order remove */
    for (i = 0; i < 1; i++)
    {
        int size = 0;
        int loops = (rand() % (size_of_arr) + 1);
        int idxs[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        int random = rand() % (size_of_arr);

        printf(BOLDWHITE "\nEmpty List\n" RESETCOLOR);
        PrintTest(AVLIsEmpty(tree), 1, "IsEmpty", __LINE__);

        for (j = 0; j < loops; j++)
        {
            while (idxs[random] == -1)
            {
                random = rand() % (size_of_arr);
            }

            idxs[random] = -1;

            printf(BOLDWHITE "\nTrying to add %d\n" RESETCOLOR, random);

            AddElementAndTest(tree, &arr[random], ++size);
        }

        for (j = 0; j < loops; j++)
        {
            random = rand() % (size_of_arr);

            while (idxs[random] != -1)
            {
                random = rand() % (size_of_arr);
            }
            idxs[random] = 0;

            printf(BOLDWHITE "\nTrying to remove %d\n" RESETCOLOR, random);

            RemoveElementAndTest(tree, &arr[random], AVLSize(tree));
        }
    }

    AVLDestroy(tree);
    tree = NULL;
}

void ShowTree(void)
{
    printf("\nTree should look:\n\n");
    printf("                  5             \n");
    printf("        1         |       9     \n");
    printf("    0   |     4   |   7   |  10 \n");
    printf("        |   3 |   | 6 | 8 |     \n");
    printf("        | 2 | |    |   |   |     \n");

    /*
                  5             \n
        1         |       9     \n
    0   |     4   |   7   |  10 \n
        |   3 |   | 6 | 8 |     \n
        | 2 | |    |   |   |     \n

    */
}

#include <stdio.h>  /* printf() */
#include <stdlib.h> /* system() */
#include <string.h> /* strncmp() */
#include <assert.h> /* assert() */

#include "circular_buffer.h" /* Create(), Destroy(), Get(), Put() */
                             /* Capacity(), IsEmpty(), FreeSpaceLeft() */

#define GREEN "\033[32m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define BOLDWHITE "\033[1m\033[37m"
#define RESETCOLOR "\033[0m"

void RunTest(void);
void PrintTest(ssize_t result, ssize_t expected, char *test_name, size_t line);
static void ResetStackBuffer(char *buff, size_t len);

int main()
{
    RunTest();
    return 0;
}

void PrintTest(ssize_t result, ssize_t expected, char *test_name, size_t line)
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
    size_t ret_val = 0;
    char stack_buff[6] = {0};
    circ_buff_t *circ_buff = CircBuffCreate(6);

    system("clear");

    printf(BOLDWHITE "\n\t\tTest Circular Buffer\n\n" RESETCOLOR);

    printf(BOLDWHITE "\nNew Empty Buffer\n" RESETCOLOR);

    PrintTest(CircBuffCapacity(circ_buff), 6, "Capacity", __LINE__);
    PrintTest(CircBuffIsEmpty(circ_buff), 1, "IsEmpty", __LINE__);
    PrintTest(CircBuffFreeSpaceLeft(circ_buff), 6, "FreeSpaceLeft", __LINE__);

    printf(BOLDWHITE "\nReading from an empty buffer\n" RESETCOLOR);
    ret_val = CircBuffGet(circ_buff, stack_buff, 3);

    PrintTest(ret_val, 0, "Get", __LINE__);
    PrintTest(CircBuffCapacity(circ_buff), 6, "Capacity", __LINE__);
    PrintTest(CircBuffIsEmpty(circ_buff), 1, "IsEmpty", __LINE__);
    PrintTest(CircBuffFreeSpaceLeft(circ_buff), 6, "FreeSpaceLeft", __LINE__);

    printf(BOLDWHITE "\nWriting 2 bytes to buffer\n" RESETCOLOR);
    ret_val = CircBufPut(circ_buff, "hi", 2);

    PrintTest(ret_val, 2, "Put", __LINE__);
    PrintTest(CircBuffCapacity(circ_buff), 6, "Capacity", __LINE__);
    PrintTest(CircBuffIsEmpty(circ_buff), 0, "IsEmpty", __LINE__);
    PrintTest(CircBuffFreeSpaceLeft(circ_buff), 4, "FreeSpaceLeft", __LINE__);

    printf(BOLDWHITE "\nReading 2 bytes of buffer\n" RESETCOLOR);
    ret_val = CircBuffGet(circ_buff, stack_buff, 2);

    PrintTest(ret_val, 2, "Get", __LINE__);
    PrintTest(CircBuffCapacity(circ_buff), 6, "Capacity", __LINE__);
    PrintTest(CircBuffIsEmpty(circ_buff), 1, "IsEmpty", __LINE__);
    PrintTest(CircBuffFreeSpaceLeft(circ_buff), 6, "FreeSpaceLeft", __LINE__);
    PrintTest(strncmp(stack_buff, "hi", 2), 0, "strncmp", __LINE__);
    ResetStackBuffer(stack_buff, 6);

    printf(BOLDWHITE "\nWriting 6 bytes to buffer (full capacity)\n" RESETCOLOR);
    ret_val = CircBufPut(circ_buff, "full-buffer", 10);

    PrintTest(ret_val, 6, "Put", __LINE__);
    PrintTest(CircBuffCapacity(circ_buff), 6, "Capacity", __LINE__);
    PrintTest(CircBuffIsEmpty(circ_buff), 0, "IsEmpty", __LINE__);
    PrintTest(CircBuffFreeSpaceLeft(circ_buff), 0, "FreeSpaceLeft", __LINE__);

    printf(BOLDWHITE "\nWriting to a full buffer\n" RESETCOLOR);
    ret_val = CircBufPut(circ_buff, "123", 3);

    PrintTest(ret_val, 0, "Put", __LINE__);
    PrintTest(CircBuffCapacity(circ_buff), 6, "Capacity", __LINE__);
    PrintTest(CircBuffIsEmpty(circ_buff), 0, "IsEmpty", __LINE__);
    PrintTest(CircBuffFreeSpaceLeft(circ_buff), 0, "FreeSpaceLeft", __LINE__);

    printf(BOLDWHITE "\nReading 6 bytes of buff\n" RESETCOLOR);
    ret_val = CircBuffGet(circ_buff, stack_buff, 10);

    PrintTest(ret_val, 6, "Get", __LINE__);
    PrintTest(CircBuffCapacity(circ_buff), 6, "Capacity", __LINE__);
    PrintTest(CircBuffIsEmpty(circ_buff), 1, "IsEmpty", __LINE__);
    PrintTest(CircBuffFreeSpaceLeft(circ_buff), 6, "FreeSpaceLeft", __LINE__);
    PrintTest(strncmp(stack_buff, "full-buffer", 6), 0, "strncmp", __LINE__);

    CircBuffDestroy(circ_buff);
}

static void ResetStackBuffer(char *buff, size_t len)
{
    size_t i = 0;
    assert(buff);

    for (i = 0; i < len; i++)
    {
        buff[i] = 0;
    }
}
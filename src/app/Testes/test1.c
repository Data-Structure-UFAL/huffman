#include "../adt.h"
//#include "../utils.h"
#include "unity.h"

void setUp(){};

void tearDown(){};

void test_funcao()
{
    Huff_Queue *queue = NULL;
    queue->head = NULL;
    TEST_ASSERT_EQUAL(1, is_empty_queue(queue));
}

void test_funcao1()
{
    int i = 0;
    TEST_ASSERT_EQUAL(1, teste(i));
}

int main()
{
    //Huff_Queue *queue = NULL;

    UNITY_BEGIN();

    RUN_TEST(test_funcao);

    return UNITY_END();
}
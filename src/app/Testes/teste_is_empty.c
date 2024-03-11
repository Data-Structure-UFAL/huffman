#include "../adt.h"
//#include "../utils.h"
#include "Unity/unity.h"

void setUp(){};

void tearDown(){};

void test_funcao_is_empty_true()
{
    //TEST_IGNORE();

    Huff_Queue *queue = create_queue();
    TEST_ASSERT_EQUAL(1, is_empty_queue(queue));
}

void test_funcao_is_empty_false()
{
    //TEST_IGNORE();

    Huff_Queue *queue = create_queue();

    Node *new_node = create_node(65, 30);

    enqueue_priority(queue, new_node);

    TEST_ASSERT_EQUAL(0, is_empty_queue(queue));
}

int main()
{

    UNITY_BEGIN();

    RUN_TEST(test_funcao_is_empty_true);
    RUN_TEST(test_funcao_is_empty_false);

    return UNITY_END();
}
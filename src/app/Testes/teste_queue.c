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

    Node *new_node = create_node('a', 30);

    enqueue_priority(queue, new_node);

    TEST_ASSERT_EQUAL(0, is_empty_queue(queue));
}

int testando_funcao_is_empty()
{
    UNITY_BEGIN();

    RUN_TEST(test_funcao_is_empty_true);
    RUN_TEST(test_funcao_is_empty_false);

    return UNITY_END();
}



int main()
{
    int opcao;

    puts("Selecione a opção que você gostaria de testar");
    puts("1 - Is_Empty");
    puts("2 - Enqueue_Priority");
    puts("3 - Dequeue");

    scanf("%d", &opcao);

    switch (opcao)
    {
        case 1:
            testando_funcao_is_empty();
            break;
        case 2:

            break;
        case 3:
            
            break;
        default:
            puts("Opcao Invalida.");
            break;
    }
    
}
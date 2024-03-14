#include "../adt.h"
//#include "../utils.h"
#include "Unity/unity.h"

void setUp(){};

void tearDown(){};

void test_funcao_dequeue_underflow()
{
    TEST_IGNORE();

    Huff_Queue *queue = create_queue();

    //PRECISO DA FUNCAO PARA COMPARAR COM UMA STRING
    //TEST_ASSERT_EQUAL('Queue Underflow\n', dequeue(queue));

}

void test_funcao_dequeue_true()
{
    //TEST_IGNORE();
    
    //criamos a fila
    Huff_Queue *queue = create_queue();

    //criamos alguns nos
    Node *new_node1 = create_node('b', 29);
    Node *new_node2 = create_node('c', 30);
    Node *new_node3 = create_node('a', 28);


    //adicionamos os nos na fila
    enqueue_priority(queue, new_node1);
    enqueue_priority(queue, new_node2);
    enqueue_priority(queue, new_node3);

    //fizemos o dequeue, que retorna o no que foi feito o dequeue
    //que no nosso caso, sera o new_node 3
    Node *dequeued = dequeue(queue);

    //aqui, testamos se o no que a funcao dequeue retornou foi o mesmo
    //que mandamos fazer o dequeue
    TEST_ASSERT_EQUAL_PTR(new_node3, dequeued);
}

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

int testando_funcao_enqueue_priority()
{
    UNITY_BEGIN();

    //RUN_TEST();
    //RUN_TEST();

    return UNITY_END();
}

int testando_funcao_dequeue()
{
    UNITY_BEGIN();

    RUN_TEST(test_funcao_dequeue_underflow);
    RUN_TEST(test_funcao_dequeue_true);

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
            testando_funcao_dequeue();
            break;
        default:
            puts("Opcao Invalida.");
            break;
    }
    
}
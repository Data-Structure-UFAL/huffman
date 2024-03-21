#include "../app/adt.h"
#include "../app/utils.h"
//#include "../app/huffman.h"
#include "Unity/unity.h"

void setUp(){};

void tearDown(){};

void teste_fila()
{
    //TEST_IGNORE();
    
    //criamos a fila
    Huff_Queue *queue = create_queue();

    //criamos alguns nos com valores variados sem seguir um padrao
    int frequencia = 2;
    char item = 'b';
    Node *new_node1 = create_node(&item, &frequencia);

    frequencia = 3;
    item = 'c';
    Node *new_node2 = create_node(&item, &frequencia);
    
    frequencia = 1;
    item = 'a';
    Node *new_node3 = create_node(&item, &frequencia);
    
    frequencia = 4;
    item = 'd';
    Node *new_node4 = create_node(&item, &frequencia);
    
    frequencia = 8;
    item = 'h';
    Node *new_node5 = create_node(&item, &frequencia);
    
    frequencia = 7;
    item = 'g';
    Node *new_node6 = create_node(&item, &frequencia);
    
    frequencia = 9;
    item = 'i';
    Node *new_node7 = create_node(&item, &frequencia);
    
    frequencia = 6;
    item = 'f';
    Node *new_node8 = create_node(&item, &frequencia);
    
    frequencia = 10;
    item = 'j';
    Node *new_node9 = create_node(&item, &frequencia);
    
    frequencia = 5;
    item = 'e';
    Node *new_node10 = create_node(&item, &frequencia);


    //adicionamos os nos na fila na ordem que criamos os mesmos
    enqueue_priority(queue, new_node1);
    enqueue_priority(queue, new_node2);
    enqueue_priority(queue, new_node3);
    enqueue_priority(queue, new_node4);
    enqueue_priority(queue, new_node5);
    enqueue_priority(queue, new_node6);
    enqueue_priority(queue, new_node7);
    enqueue_priority(queue, new_node8);
    enqueue_priority(queue, new_node9);
    enqueue_priority(queue, new_node10);


    //fizemos o dequeue, que retorna o no que foi feito o dequeue ate a lista ficar vazia
    //no caso testamos 10 vezes
    //se em um dos casos falhar, o teste falha como um todo
    //a ordem que eh feita os dequeues eh new_node 3, 1, 2, 4, 10, 8, 6, 5, 7, 9
    //caso mudemos essa ordem de teste, o teste vai dar erro

    TEST_ASSERT_EQUAL_PTR(new_node3, dequeue(queue));

    TEST_ASSERT_EQUAL_PTR(new_node1, dequeue(queue));

    TEST_ASSERT_EQUAL_PTR(new_node2, dequeue(queue));

    TEST_ASSERT_EQUAL_PTR(new_node4, dequeue(queue));

    TEST_ASSERT_EQUAL_PTR(new_node10, dequeue(queue));

    TEST_ASSERT_EQUAL_PTR(new_node8, dequeue(queue));

    TEST_ASSERT_EQUAL_PTR(new_node6, dequeue(queue));

    TEST_ASSERT_EQUAL_PTR(new_node5, dequeue(queue));

    TEST_ASSERT_EQUAL_PTR(new_node7, dequeue(queue));

    TEST_ASSERT_EQUAL_PTR(new_node9, dequeue(queue));

    //aqui, testamos se o no que a funcao dequeue retornou foi o mesmo
    //que mandamos fazer o dequeue para todos os casos.

    return;
}

void teste_huff_tree()
{
    //TEST_IGNORE();
    
    //criamos a fila
    Huff_Queue *queue = create_queue();

    //criamos alguns nos com valores variados sem seguir um padrao
    int frequencia = 2;
    char item = 'b';
    Node *new_node1 = create_node(&item, &frequencia);

    frequencia = 3;
    item = 'c';
    Node *new_node2 = create_node(&item, &frequencia);
    
    frequencia = 1;
    item = 'a';
    Node *new_node3 = create_node(&item, &frequencia);
    
    frequencia = 4;
    item = 'd';
    Node *new_node4 = create_node(&item, &frequencia);
    
    frequencia = 8;
    item = 'h';
    Node *new_node5 = create_node(&item, &frequencia);
    
    frequencia = 7;
    item = 'g';
    Node *new_node6 = create_node(&item, &frequencia);
    
    frequencia = 9;
    item = 'i';
    Node *new_node7 = create_node(&item, &frequencia);
    
    frequencia = 6;
    item = 'f';
    Node *new_node8 = create_node(&item, &frequencia);
    
    frequencia = 10;
    item = 'j';
    Node *new_node9 = create_node(&item, &frequencia);
    
    frequencia = 5;
    item = 'e';
    Node *new_node10 = create_node(&item, &frequencia);


    //adicionamos os nos na fila na ordem que criamos os mesmos
    enqueue_priority(queue, new_node1);
    enqueue_priority(queue, new_node2);
    enqueue_priority(queue, new_node3);
    enqueue_priority(queue, new_node4);
    enqueue_priority(queue, new_node5);
    enqueue_priority(queue, new_node6);
    enqueue_priority(queue, new_node7);
    enqueue_priority(queue, new_node8);
    enqueue_priority(queue, new_node9);
    enqueue_priority(queue, new_node10);

    //aqui estamos criando a arvore de huffman
    Node *root = create_huffman_tree(queue);
    
    //Para simplificar, estou testando para saber se o caminho das folhas esta correto
    TEST_ASSERT_EQUAL_CHAR('a', *(unsigned char *) root->left->right->left->left->left->byte);

    TEST_ASSERT_EQUAL_CHAR('b', *(unsigned char *) root->left->right->left->left->right->byte);

    TEST_ASSERT_EQUAL_CHAR('c', *(unsigned char *) root->left->right->left->right->byte);

    TEST_ASSERT_EQUAL_CHAR('d', *(unsigned char *) root->right->right->left->left->byte);

    TEST_ASSERT_EQUAL_CHAR('e', *(unsigned char *) root->right->right->left->right->byte);

    TEST_ASSERT_EQUAL_CHAR('f', *(unsigned char *) root->left->right->right->byte);

    TEST_ASSERT_EQUAL_CHAR('g', *(unsigned char *) root->right->left->left->byte);

    TEST_ASSERT_EQUAL_CHAR('h', *(unsigned char *) root->right->left->right->byte);
    
    TEST_ASSERT_EQUAL_CHAR('i', *(unsigned char *) root->right->right->right->byte);

    TEST_ASSERT_EQUAL_CHAR('j', *(unsigned char *) root->left->left->byte);

    return;
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(teste_fila);
    RUN_TEST(teste_huff_tree);
    //teste_huff_tree();

    return UNITY_END();
}
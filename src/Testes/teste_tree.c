#include "../adt.h"
//#include "../utils.h"
#include "Unity/unity.h"

void setUp(){};

void tearDown(){};

void opcoes()
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
            testando_funcao_priority_enqueue();
            break;
        case 3:
            testando_funcao_dequeue();
            break;
        default:
            puts("Opcao Invalida.");
            puts("Selecione outra opcao.");
            opcoes();
            break;
    }

    return;
}

int main()
{
    opcoes();

    return 0;    
}
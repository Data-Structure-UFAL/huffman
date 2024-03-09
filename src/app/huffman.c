#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "adt.h"


int main()
{
    int choice = initial_message();
    char path[255];

    puts("Digite o caminho do arquivo\n");
    scanf("%s", path);
  
    switch (choice)
    {
    case 1:
        printf("Comprindo arquivo: %s\n", path);
        break;

    case 2:
        printf("Descomprindo arquivo: %s\n", path);
        break;
    
    default:
        puts("Digite uma escolha válida!");
        break;
    }

    return 0;
}
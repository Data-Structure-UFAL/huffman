#include <stdio.h>
#include <stdlib.h>

int main()
{
    int option;
    
    puts("BEM VINDO AO HUFFMAN");
    puts("ESCOLHA A OPCAO DESEJADA");
    puts("1 - COMPACTAR");
    puts("2 - DESCOMPACTAR");

    scanf("%d", &option);

    char caminho[1000];
    //compactar
    if(option == 1)
    {
        puts("POR FAVOR, DIGITE O ENDERECO DA PASTA DO ARQUIVO QUE VOCE DESEJA COMPACTAR");
        scanf("%s", caminho);
    }

    //descompactar
    else if(option == 2)
    {
        puts("POR FAVOR, DIGITE O ENDERECO DA PASTA DO ARQUIVO QUE VOCE DESEJA DESCOMPACTAR");
        scanf("%s", caminho);
    }
    else 
    {
        puts("OPCAO INVALIDA");
        return 0;
    }
}
#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <stdlib.h>
#define ASCII_LENGTH 256

typedef struct {
  unsigned char * byte;
  long size;
} object_data;





/*  
    # OBJETIVO: ler qualquer tipo de arquivo e conseguir ter os bits para uma posterior manipulação
    # PARAMETRO: É passado o caminho do arquivo, como por exemplo "src/app/imagem.png"
    # RETORNO: É retornado um struct do tipo object_data que contem um 'byte' armazenando os bits e um 'size' armazenando o tamanho do arquivo (numero de bytes)

*/

object_data *read_initial_file(char name_file[]);


/* 
    # OBJETIVO: Contar a frequência de cada byte do arquivo lido
    # PARAMETRO:  É passado um struct do tipo object_data com informações da sequência de bytes e o numero de bytes 
        e um array de inteiros que irá armazenar a frequência dos bytes.
    # RETORNO: Não é retornado nada, mas o array de frequencia que é passado é alterado no escopo em que a fnção foi chamada
*/

void get_frequency(object_data * data, int arr_frequency[]);














object_data *read_initial_file(char name_file[]) {
    object_data *data_file = (object_data *)malloc(sizeof(object_data));


    if (data_file == NULL) {
        printf("Erro ao alocar memória para data_file!\n");
        abort();
    }

    FILE *file;
    file = fopen(name_file, "rb");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s!\n", name_file);
        free(data_file);
        abort();
    }

    fseek(file, 0, SEEK_END);
    data_file->size = ftell(file);
    fseek(file, 0, SEEK_SET);

    data_file->byte = (unsigned char *)malloc(data_file->size * sizeof(unsigned char));

    if (data_file->byte == NULL) {
        printf("Erro ao alocar memória para data_file->data!\n");
        fclose(file);
        free(data_file);
        abort();
    }

    fread(data_file->byte, sizeof(unsigned char), data_file->size, file);

    fclose(file);

    return data_file;
}


void get_frequency(object_data * data, int arr_frequency[]){

    for (int i = 0; i < ASCII_LENGTH; i++)
    {
       arr_frequency[i] = 0;
    }
    
    for (int i = 0; i < data->size; i++)
    {
       arr_frequency[data->byte[i]]++;
    }

}


#endif
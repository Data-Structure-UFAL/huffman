#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  unsigned char * data;
  long size;
} object_data;

object_data *read_file(char name_file[]) {
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

    data_file->data = (unsigned char *)malloc(data_file->size * sizeof(unsigned char));

    if (data_file->data == NULL) {
        printf("Erro ao alocar memória para data_file->data!\n");
        fclose(file);
        free(data_file);
        abort();
    }

    fread(data_file->data, sizeof(unsigned char), data_file->size, file);

    fclose(file);

    return data_file;
}


#endif
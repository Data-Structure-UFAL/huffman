#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
  unsigned char * data;
  long size;
} object_data;

object_data * read_file(char name_file[]){

    object_data * data_file = malloc(sizeof(object_data));

    FILE *file;
    file = fopen(name_file, "rb");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        abort();
    }

    fseek(file, 0, SEEK_END); 
    data_file->size = ftell(file); 
    fseek(file, 0, SEEK_SET);
    
    data_file->data = malloc(data_file->size * sizeof(unsigned char));
    fread(data_file->data, sizeof(unsigned char), data_file->size, file);

    fclose(file);

    return data_file;
}

/* void create_file(char path[], object_data * data_file){
    FILE *file;
    file = fopen(path, "wb");

    fwrite(data_file->data, sizeof(unsigned char), data_file->size, file);
    fclose(file); 
}
 */

int main(){
    /* char path[] = "image.png";
    object_data * data_file = read_file(path); */

    /* char path_output[] = "created_image.png";
    create_file(path_output, data_file); */
   
    
    return 0;

}
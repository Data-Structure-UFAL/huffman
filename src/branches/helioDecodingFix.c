// após adicionar essa função, modificar em app/huffman.h: a chamada do decoding para: decoding(huff_tree->root, qts_bytes_completos, tree_size, trash);
//

void decoding(Node *root, int qts_bytes_completos, int treeSize, int trashSize) {
    FILE *compress_file = fopen("compress.huff", "rb");

    if (!compress_file) {
        printf("Problema ao abrir arquivo em compress_file\n");
        return;
    }

    FILE *decompress_file = fopen("decompress.txt", "wb");
    if (!decompress_file) {
        printf("Problema ao abrir arquivo em decompress_file\n");
        fclose(compress_file); // Fechar o arquivo se não puder abrir o outro
        return;
    }

    unsigned char byte;
    Node *current = root;

    fseek(compress_file, treeSize + 2, SEEK_CUR);
    int no_trash = 8 - trashSize;

    while (fread(&byte, sizeof(unsigned char), 1, compress_file)) {
        for (int i = 7; i >= 0; i--) {
            if (qts_bytes_completos == 0 && no_trash == 0) break;

            current = (is_on_bit(byte, i)) ? current->right : current->left;

            if (qts_bytes_completos == 0 && no_trash > 0) no_trash--;

            if (current->left == NULL && current->right == NULL) {
                printf("qtdbits: %d decompress... %c\n", qts_bytes_completos, current->byte);
                fwrite(&current->byte, sizeof(unsigned char), 1, decompress_file);
                current = root;
            }
        }

        qts_bytes_completos--; 

        if (qts_bytes_completos == 0 && no_trash == 0) break;
    }

    fclose(compress_file);
    fclose(decompress_file);
}
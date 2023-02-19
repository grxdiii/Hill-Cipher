#include "stdio.h"
#include "stdlib.h"

#include "matrix.h"
#include "text.h"

int main(int argc, char *argv[]) 
{
    FILE *key_file = fopen(argv[1], "r");
    FILE *plaintext_file = fopen(argv[2], "r");

    /* Variables to store our matrix and its size */
    int **key_matrix, matrix_size; 

    /* Variables to store single words and plain text */
    char buffer[WORD_LENGHT]; char *plaintext = NULL;

    /* Produces our matrix as desired */
    key_matrix = store_matrix(key_file, key_matrix, &matrix_size);
    print_matrix(key_matrix, matrix_size);

    /* Reads our text file as desired */
    plaintext = read_plaintext(plaintext_file, buffer, matrix_size);

    free_plaintext(plaintext);
    free_matrix(key_matrix, matrix_size);
    fclose(key_file);
    fclose(plaintext_file);

    return 0;
}
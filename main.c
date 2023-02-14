#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define WORD_LENGTH 45

int **store_matrix(FILE *key_file, int **key_matrix, int *matrix_size);
void print_matrix(int **key_matrix, int matrix_size);
void remove_special_characters(char *buffer);
void read_plaintext(FILE *plaintext_file, char *buffer);

int main(int argc, char *argv[]) {
    /* Our programm will start by opening the key and plain text file 
     * The user will be expected to input the name of these files during execution */
    FILE *key_file = fopen(argv[1], "r");
    FILE *plaintext_file = fopen(argv[2], "r");

    char buffer[WORD_LENGTH]; 

    /* Variables to store our matrix and its size */
    int **key_matrix, matrix_size; 
    
    /* Produces our matrix as desired */
    key_matrix = store_matrix(key_file, key_matrix, &matrix_size);
    print_matrix(key_matrix, matrix_size);
    read_plaintext(plaintext_file, buffer);

    fclose(key_file);
    fclose(plaintext_file);

    return 0;
}

/* This function will read our key file and produce our desired matrix */
int **store_matrix(FILE *key_file, int **key_matrix, int *matrix_size) {
    int value;

    /* Reads the first line from our key file and allocates spaces for our matrix based on that number */
    fscanf(key_file, "%d", matrix_size);
    key_matrix = malloc(sizeof(int *) * (*matrix_size));

    /* Our matrix will be stored in a 2d array allocated in the heap */
    for(int i = 0; i < (*matrix_size); i++) {
        int *row_values = malloc(sizeof(int) * (*matrix_size));
        key_matrix[i] = row_values;

        for(int j = 0; j < (*matrix_size); j++) {
            fscanf(key_file, "%d", &key_matrix[i][j]);
        }
    }

    return key_matrix;
}

/* Prints our key matrix */
void print_matrix(int **key_matrix, int matrix_size) {
    printf("Key matrix: \n");

    for(int i = 0; i < matrix_size; i++) {
        for(int j = 0; j < matrix_size; j++) {
            printf("  %d ", key_matrix[i][j]);
        }
        printf("\n");
    }

    printf("\n\n");
}

void remove_special_characters(char *buffer) {
    int ascii_value;

    for(int i = 0; i < strlen(buffer); i++) {
        ascii_value = buffer[i];

        if(ascii_value < 48 || (ascii_value > 57 && ascii_value < 65) || (ascii_value > 99 && ascii_value < 97) || ascii_value > 122) {
            memmove(buffer + i, buffer + i + 1, strlen(buffer) - 1);
        }
    }
}

void read_plaintext(FILE *plaintext_file, char *buffer) {
    int char_count = 0;

    while(feof(plaintext_file) == 0) {
        fscanf(plaintext_file, "%s", buffer);
        remove_special_characters(buffer);
        printf("%s", buffer);
        char_count += strlen(buffer);
    }
}
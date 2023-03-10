#ifndef MATRIX_H
#define MATRIX_H

#include "string.h"

int **store_matrix(FILE *key_file, int **key_matrix, int *matrix_size);

void print_matrix(int **key_matrix, int matrix_size);
void free_matrix(int **key_matrix, int matrix_size);

void matrix_multiplication(char *plaintext, char *cyphertext, int **key_matrix, int matrix_size, int location);
char *produce_cyphertext(char *plaintext, int **key_matrix, int matrix_size);

#endif
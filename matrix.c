#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "matrix.h"

/* store_matrix: reads key file and produce desired matrix */
int **store_matrix(FILE *key_file, int **key_matrix, int *matrix_size) 
{
    int value;

    /* allocates space for matrix */
    fscanf(key_file, "%d", matrix_size);
    key_matrix = malloc(sizeof(int *) * (*matrix_size));

    /* store values within matrix in 2d array */
    for(int i = 0; i < (*matrix_size); i++) 
    {
        int *row_values = malloc(sizeof(int) * (*matrix_size));
        key_matrix[i] = row_values;

        for(int j = 0; j < (*matrix_size); j++) {
            fscanf(key_file, "%d", &key_matrix[i][j]);
        }
    }

    return key_matrix;
}

/* print_matrix: prints values within matrix */
void print_matrix(int **key_matrix, int matrix_size) 
{
    printf("Key matrix: \n");

    for(int i = 0; i < matrix_size; i++) 
    {
        for(int j = 0; j < matrix_size; j++) {
            printf(" %2d ", key_matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

/* free_matrix: free memory allocated for the matrix */
void free_matrix(int **key_matrix, int matrix_size) 
{
    for(int i = 0; i < matrix_size; i++) 
    {
        free(key_matrix[i]);
    }

    free(key_matrix);
    key_matrix = NULL;
}

/* matrix_multiplication: encrypts cypher text */
void matrix_multiplication(char *plaintext, char *cyphertext, int **key_matrix, int matrix_size, int location)
{
    int letter_value, temp_location;

    /* loops through the key matrix */
    for(int i = 0; i < matrix_size; i++)
    {
        temp_location = location - i;
        letter_value = 0;

        /* find character's alpha value and multiplies it with the matrix */
        for(int j = 0; j < matrix_size; j++)
        {
            letter_value = letter_value + (key_matrix[i][j] * (plaintext[temp_location] - 97));
            temp_location++;
        }
        
        cyphertext[location] = (letter_value % 26) + 97;
        location++;
    }
}

/* produce_cyphertext: produces cypher text as desired */
char *produce_cyphertext(char *plaintext, int **key_matrix, int matrix_size)
{
    /* allocates space for cypher text */
    char *cyphertext = malloc(sizeof(char *) * (strlen(plaintext) + 1));

    /* encrypts the plain text */
    for(int i = 0; i < strlen(plaintext); i += matrix_size) 
    {
        matrix_multiplication(plaintext, cyphertext, key_matrix, matrix_size, i);
    }

    /* prints cypher text */
    printf("Cyphertext: \n%s\n", cyphertext);

    return cyphertext;
}
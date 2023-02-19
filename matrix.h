/* This function will read our key file and produce our desired matrix */
int **store_matrix(FILE *key_file, int **key_matrix, int *matrix_size) 
{
    int value;

    /* Reads the first line from our key file and allocates spaces for our matrix based on that number */
    fscanf(key_file, "%d", matrix_size);
    key_matrix = malloc(sizeof(int *) * (*matrix_size));

    /* Our matrix will be stored in a 2d array allocated in the heap */
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

/* Prints our key matrix */
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

/* Frees the memory allocated through malloc */
void free_matrix(int **key_matrix, int matrix_size) 
{
    for(int i = 0; i < matrix_size; i++) 
    {
        free(key_matrix[i]);
    }

    free(key_matrix);
    key_matrix = NULL;
}
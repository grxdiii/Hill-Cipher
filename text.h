#include "stdio.h"
#include "ctype.h"
#include "string.h"

#define WORD_LENGHT 200

void remove_special_characters(char *buffer) 
{
    for(int i = 0; buffer[i]; i++) 
    {
        buffer[i] = tolower(buffer[i]);

        if(!(buffer[i] >= 'a' && buffer[i] <= 'z'))
        {
            for(int j = i; buffer[j]; j++) 
            { 
                buffer[j] = buffer[j + 1];
            }

            i--;
        }  
    }

}

void plainttext_padding(char *plainttext, int matrix_size, int *characters_read)
{
    int pad_by = matrix_size - (*characters_read % matrix_size);
    char *pad_values;

    if(pad_by == matrix_size) 
    {
        return ;
    }

    pad_values = malloc(sizeof(char *) * pad_by);

    for(int i = 0; i < pad_by; i++)
    {
        pad_values[i] = 'x';
    }

    strcat(plainttext, pad_values);
    *characters_read = *characters_read + pad_by;
}

void free_plaintext(char *plaintext)
{
    free(plaintext);
    plaintext = NULL;
}

char *read_plaintext(FILE *plaintext_file, char *buffer, int matrix_size) 
{
    int characters_read = 0;
    int plaintext_length = WORD_LENGHT; 

    char *plaintext = malloc(sizeof(char *) * plaintext_length);

    while(feof(plaintext_file) == 0) 
    {
        if(characters_read >= plaintext_length) 
        {
            plaintext_length = plaintext_length + WORD_LENGHT;
            plaintext = realloc(plaintext, sizeof(char *) * plaintext_length);
        }

        fscanf(plaintext_file, "%s", buffer);
        remove_special_characters(buffer);

        characters_read = characters_read + strlen(buffer);
        strcat(plaintext, buffer);
    }

    plainttext_padding(plaintext, matrix_size, &characters_read);
    printf("Plaintext: \n%s\n", plaintext);

    return plaintext;
}


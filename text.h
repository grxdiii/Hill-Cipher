#include "stdio.h"
#include "ctype.h"
#include "string.h"

#define WORD_LENGHT 200

/* Removes all non-alphabetic characters from our string */
void remove_special_characters(char *buffer) 
{
    /* Loops through our string until we hit the null terminator */ 
    for(int i = 0; buffer[i]; i++) 
    {
        buffer[i] = tolower(buffer[i]);

        /* Checks to see if our character is non-alphabetic or uppercase */
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

/* Pads our plain text as needed */
void plainttext_padding(char *plainttext, int matrix_size, int *characters_read)
{
    /* Calculates by how much we should pad */
    int pad_by = matrix_size - (*characters_read % matrix_size);
    char *pad_values;

    if(pad_by == matrix_size) 
    {
        return ;
    }

    /* Allocates space for the characters we'll use to pad */
    pad_values = malloc(sizeof(char *) * pad_by);

    /* Adds those characters to our plain text string */
    for(int i = 0; i < pad_by; i++)
    {
        pad_values[i] = 'x';
    }

    strcat(plainttext, pad_values);
    *characters_read = *characters_read + pad_by;
}

/* Frees the memory allocated through malloc */
void free_text(char *text)
{
    free(text);
    text = NULL;
}

/* Reads our plain text file */
char *read_plaintext(FILE *plaintext_file, char *buffer, int matrix_size) 
{
    /* Variables used to keep track of our string length, as well as how many characters are in our file */
    int characters_read = 0;
    int plaintext_length = WORD_LENGHT; 

    /* The string containing our plain text will be allocated with malloc - this allows us to not waste memory. 
     * This is inspired by the ArrayList data structure found in java, where we have an initial size and we allocate more space to our array if needed */
    char *plaintext = malloc(sizeof(char *) * plaintext_length);

    /* Loops through our entire file */
    while(feof(plaintext_file) == 0) 
    {
        /* Checks to see if we have space to add our newly read word to our plain text string */
        if(characters_read >= plaintext_length) 
        {
            plaintext_length = plaintext_length + WORD_LENGHT;
            plaintext = realloc(plaintext, sizeof(char *) * plaintext_length);
        }

        /* Scans our string and remove any special characters */
        fscanf(plaintext_file, "%s", buffer);
        remove_special_characters(buffer);

        /* Appends our word to our plain text string */
        characters_read = characters_read + strlen(buffer);
        strcat(plaintext, buffer);
    }

    /* Pads our text file if needed based on the requirements laid down on our instruction file */
    plainttext_padding(plaintext, matrix_size, &characters_read);
    printf("Plaintext: \n%s\n\n", plaintext);

    return plaintext;
}


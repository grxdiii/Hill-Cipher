#include <stdio.h>
#include <stdlib.h>

#include "ctype.h"
#include "string.h"

#include "text.h"

/* remove_special_characters: removes all non-alphabetic characters from given string */
void remove_special_characters(char *buffer) 
{
    /* loops through our string until we hit the null terminator */ 
    for(int i = 0; buffer[i]; i++) 
    {
        buffer[i] = tolower(buffer[i]);

        /* checks to see if our character is non-alphabetic or uppercase */
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

/* plaintext_padding: pads plain text as needed, adding n number of x at the end */
void plaintext_padding(char *plainttext, int matrix_size, int *characters_read)
{
    /* calculates how much x to add */
    int pad_by = matrix_size - (*characters_read % matrix_size);
    char *pad_values;

    if(pad_by == matrix_size) 
    {
        return ;
    }

    /* allocates space for the characters we'll use to pad */
    pad_values = malloc(sizeof(char *) * pad_by);

    /* adds those characters to our plain text string */
    for(int i = 0; i < pad_by; i++)
    {
        pad_values[i] = 'x';
    }

    strcat(plainttext, pad_values);
    *characters_read = *characters_read + pad_by;
}

/* free_text: frees memory allocated through malloc */
void free_text(char *text)
{
    free(text);
    text = NULL;
}

/* read_plaintext: reads plain text file */
char *read_plaintext(FILE *plaintext_file, char *buffer, int matrix_size) 
{
    /* variables used to keep track of our string length, as well as how many characters are in our file */
    int characters_read = 0;
    int plaintext_length = WORD_LENGTH; 

    /* the string containing our plain text will be allocated with malloc */
    char *plaintext = malloc(sizeof(char *) * plaintext_length);

    /* loops through our entire file */
    while(feof(plaintext_file) == 0) 
    {
        /* checks to see if we have space to add the newly read word to the plain text string */
        if(characters_read >= plaintext_length) 
        {
            plaintext_length = plaintext_length + WORD_LENGTH;
            plaintext = realloc(plaintext, sizeof(char *) * plaintext_length);
        }

        /* scans string and remove any special characters */
        fscanf(plaintext_file, "%s", buffer);
        remove_special_characters(buffer);

        /* appends our word to the plain text string */
        characters_read = characters_read + strlen(buffer);
        strcat(plaintext, buffer);
    }

    /* pads our text file if needed based on the requirements laid down on our instruction file */
    plaintext_padding(plaintext, matrix_size, &characters_read);
    printf("Plaintext: \n%s\n\n", plaintext);

    return plaintext;
}


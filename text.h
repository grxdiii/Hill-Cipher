#ifndef TEXT_H
#define TEXT_H

#define WORD_LENGTH 200

void remove_special_characters(char *buffer);
void plaintext_padding(char *plainttext, int matrix_size, int *characters_read);
void free_text(char *text);

char *read_plaintext(FILE *plaintext_file, char *buffer, int matrix_size);

#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "header.h"


char* parsing_handler(char input_string[]) 
{
    char delimiter[] = " ";
    char *p_first_tokenized_string;
    char **parsed_string = NULL;
    int index = 0, size = 1;

    // allocate for an array of pointer to strings 
    parsed_string = malloc(1 * sizeof(char*));

    p_first_tokenized_string = strtok(input_string, delimiter);

    while (p_first_tokenized_string != NULL) 
    {
        parsed_string = realloc(parsed_string, size * sizeof(char*));
        parsed_string[index] = p_first_tokenized_string;

        size++;
        index++;

        p_first_tokenized_string = strtok(NULL, delimiter);
    }

    
    for (int i = 0; i < size - 1; i++) 
    {
        printf("%s\n", parsed_string[i]);
    }

    free(parsed_string); 
    return *parsed_string;
}
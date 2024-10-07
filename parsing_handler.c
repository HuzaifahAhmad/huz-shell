#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "header.h"


char** parsing_handler(char input_string[]) 
{
    char delimiter[] = " ";
    char *p_first_tokenized_string;
    char **parsed_string = NULL;
    int index = 0, size = 1;

    // allocate for an array of pointer to strings 
    parsed_string = malloc(size * sizeof(char*));

    p_first_tokenized_string = strtok(input_string, delimiter);

    while (p_first_tokenized_string != NULL) 
    {
        parsed_string = realloc(parsed_string, (size + 1) * sizeof(char*));
        parsed_string[index] = p_first_tokenized_string;

        size++;
        index++;

        p_first_tokenized_string = strtok(NULL, delimiter);
    }

    parsed_string[index] = NULL;
    return parsed_string;
}
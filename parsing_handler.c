#include <stdio.h>
#include <string.h>

#include "header.h"


void parsing_handler(char input_string[]) 
{
    char delimiter[] = " ";
    char *p_first_tokenized_string;
    char parsed_string[1000];
    // char pipe_symbol[] = "|";

    p_first_tokenized_string = strtok(input_string, delimiter);

    while (p_first_tokenized_string != NULL) 
    {
        printf("%s\n", p_first_tokenized_string);
        p_first_tokenized_string = strtok(NULL, delimiter);


    }
}
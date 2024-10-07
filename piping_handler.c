#include <stdio.h>
#include <string.h>

void piping_handler(char *tokenized_array[]) 
{
    char piping_character[] = "|";

    for (int i = 0; tokenized_array[i] != NULL; i++) 
    {
        printf("after: %s\n", tokenized_array[i]);
    }


}
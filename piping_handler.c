#include <stdio.h>
#include <string.h>

void piping_handler(char **tokenized_array) 
{
    char piping_character[] = "|";

    for (int i = 0; tokenized_array[i] != NULL; i++) 
    {
        if (tokenized_array[i] == piping_character) 
        {
            printf("\n| PRESENT!\n");
        }
        printf("after: %s\n", tokenized_array[i]);
    }


}
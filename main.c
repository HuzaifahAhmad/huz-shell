#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LIMIT 100

char wildcard_globbing(char inputString[MAX_LIMIT]);

int main() {
    char get_command_from_user[MAX_LIMIT];
    char exit[] = "exit";

    printf("START OF SHELL\n");
    
    while(1) 
    {
        printf("HuzShell$ ");
        // get input from user
        fgets(get_command_from_user, MAX_LIMIT, stdin);
        printf("ORIGINAL: %s", get_command_from_user);

        // remove newline character
        get_command_from_user[strcspn(get_command_from_user, "\n")] = 0;

        // check if user wants to terminate
        if (strcmp(get_command_from_user, exit) == 0) {
            break;
        }

        // check for any wildcard characters in the input
        wildcard_globbing(get_command_from_user);
    }

    printf("\n");
    printf("THE SHELL HAS TERMINATED!");


    return 0;
}

// checks for wildcard characters (?, *, #)
char wildcard_globbing(char inputString[MAX_LIMIT]) 
{
    char question_mark = '?';
    char asterisk = '*';
    char hash_tag = '#';
    char delimiter[] = " ";
    char copyInputString[MAX_LIMIT];
    char *p_tokenized_string;
    bool isWildcard = false;

    // copy input string
    strcpy(copyInputString, inputString);

    // get first word from command
    p_tokenized_string = strtok(copyInputString, delimiter);

    // get the rest of words from command
    while (p_tokenized_string != NULL) 
    {
        // ?
        if (strchr(p_tokenized_string, question_mark) != NULL) 
        {  
            printf("?ISwildcard\n");
            isWildcard = true;
            break;
        }
        // !
        if (strchr(p_tokenized_string, asterisk) != NULL) 
        {
            printf("*ISwildcard\n");
            isWildcard = true;
            break;
        }
        // #
        if (strchr(p_tokenized_string, hash_tag) != NULL) 
        {
            printf("#ISwildcard\n");
            isWildcard = true;
            break;
        }

        // continue with the next word
        p_tokenized_string = strtok(NULL, delimiter);
    }   

    // wildcard character not present, return original
    if (!isWildcard) 
    {
        printf("RETURN ORIGINAL ARRAY\n");
        return *inputString;
    } 
    else
    {
        printf("RETURN MODIFIED ARRAY\n");
        return *copyInputString;
    }

`    
}

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <glob.h>
#include <fnmatch.h>

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
char wildcard_globbing(char input_string[MAX_LIMIT]) 
{
    char question_mark = '?';
    char asterisk = '*';
    char delimiter[] = " ";
    char copy_input_string[MAX_LIMIT];
    char *p_tokenized_string;
    bool is_wildcard = false;
    char *ptr_copy_input_string;
    char combined_command_for_globbing[250];

    // copy input string
    strcpy(copy_input_string, input_string);

    ptr_copy_input_string = copy_input_string;
    // get first word from command
    p_tokenized_string = strtok(copy_input_string, delimiter);

    // get the rest of words from command
    while (p_tokenized_string != NULL) 
    {
        // * - matches zero or more characters
        if (strchr(p_tokenized_string, asterisk) != NULL) 
        {
            glob_t pglob;
            int result_asterick = glob(p_tokenized_string, GLOB_NOCHECK, NULL, &pglob);
            for (size_t i = 0; i < pglob.gl_pathc; i++)
                printf("%s\n", pglob.gl_pathv[i]);
            globfree(&pglob);

            is_wildcard = true;
            break;
        }

        // ? - Matches exactly one character
        if (strchr(p_tokenized_string, question_mark) != NULL) 
        {  
            glob_t pglob2;
            int result_q_mark = glob(p_tokenized_string, GLOB_NOCHECK, NULL, &pglob2);
            for (size_t i = 0; i < pglob2.gl_pathc; i++)
                printf("%s\n", pglob2.gl_pathv[i]);
            globfree(&pglob2);

            is_wildcard = true;
            break;
        }

        // continue with the next word
        p_tokenized_string = strtok(NULL, delimiter);
    }   

    // wildcard character not present, return original
    if (!is_wildcard) 
    {
        printf("RETURN ORIGINAL ARRAY\n");
        printf("RETURN ARRAY: %s\n", input_string);
        return *input_string;
    } 
    else
    {
        printf("RETURN MODIFIED ARRAY\n");
        printf("RETURN ARRAY: %s\n", copy_input_string);
        return *copy_input_string;
    }
}

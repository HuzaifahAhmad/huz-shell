#include <stdio.h>
#include <string.h>
#define MAX_LIMIT 50

void wildcard_globbing(char inputString[MAX_LIMIT]);

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
void wildcard_globbing(char inputString[MAX_LIMIT]) 
{
    char question_mark = '?';
    char exclamation_mark = '*';
    char hashtag = '#';

    char delimiter[] = " ";

    // get first word from command
    char *p_tokenized_string = strtok(inputString, delimiter);

    // get the rest of words from command
    while (p_tokenized_string != NULL) 
    {
        printf("%s\n", p_tokenized_string);

        if (strchr(p_tokenized_string, question_mark) != NULL) 
        {
            printf("WILDCARD!\n");
        }



        p_tokenized_string = strtok(NULL, delimiter);
    }    

}

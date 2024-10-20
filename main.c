#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "header.h"

#define MAX_LIMIT 1000


int main() {
    char get_command_from_user[MAX_LIMIT];
    char exit[] = "exit";
    char *built_in_commands_strings[] = 
    { "cd", "pwd", "echo", "history"};

    int num_of_built_in_commands = sizeof(built_in_commands_strings) / sizeof(char *);

    printf("START OF SHELL\n");
    
    while(1) 
    {
        printf("HuzShell$ ");
        // get input from user
        fgets(get_command_from_user, MAX_LIMIT, stdin);

        // remove newline character
        get_command_from_user[strcspn(get_command_from_user, "\n")] = 0;

        // check if user wants to terminate
        if (strcmp(get_command_from_user, exit) == 0) {
            break;
        }

        print_command_history(get_command_from_user);




        // check for any wildcard characters in the input
        char *result_from_wildcard_globbing_funtion = wildcard_globbing(get_command_from_user);
        strcpy(get_command_from_user, result_from_wildcard_globbing_funtion);
        // printf("WILDCARD GLOBBING: %s\n", get_command_from_user);

        
        // parsing after expanding wildcard character
        char **parsed_command = parsing_handler(get_command_from_user);


        // checks if input is not null, then checks if the in the input is a builtin or external command and executes accordingly
        if (parsed_command[0] != NULL) 
        {
            for (int i = 0; i < num_of_built_in_commands; i++) 
            {
                if (strcmp(parsed_command[0], built_in_commands_strings[i]) == 0)
                {
                    execute_built_in_command(parsed_command);
                    break;
                }
                else 
                {
                    execute_external_command(parsed_command);
                    break;
                }
                
            }
        }

    free(parsed_command);
    }

    
    printf("\n");
    printf("THE SHELL HAS TERMINATED!");


    return 0;
}

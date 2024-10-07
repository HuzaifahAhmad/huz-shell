#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "header.h"

#define MAX_LIMIT 1000


int main() {
    char get_command_from_user[MAX_LIMIT];
    char exit[] = "exit";

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


        // check for any wildcard characters in the input
        char *result_from_wildcard_globbing_funtion = wildcard_globbing(get_command_from_user);
        strcpy(get_command_from_user, result_from_wildcard_globbing_funtion);
        printf("WILDCARD GLOBBING: %s\n", get_command_from_user);

        
        // parsing after expanding wildcard character
        char **parsed_command = parsing_handler(get_command_from_user);

        // piping handler - checks for pipes and handles accordingly
        piping_handler(parsed_command);

        free(parsed_command); 

    }

    printf("\n");
    printf("THE SHELL HAS TERMINATED!");


    return 0;
}

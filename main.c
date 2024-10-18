#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "header.h"
#include "header.h"

#define MAX_LIMIT 1000

// function to trim leading and trailing spaces
char *trim_whitespace(char *str) {
    char *end;

    // trim leading space
    while(isspace((unsigned char)*str)) str++;

    // If all spaces
    if(*str == 0)  
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end+1) = 0;

    return str;
}

int main() {
    char get_command_from_user[MAX_LIMIT];
    char exit[] = "exit";
    char *built_in_commands_strings[] = 
    { "cd", "pwd", "echo", "history"};

    int num_of_built_in_commands = sizeof(built_in_commands_strings) / sizeof(char *);
    int history_count = 0;
    int history_array_size = 10;

    char **history_of_commands = malloc(10 * sizeof(char*));
    if (history_of_commands == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

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

        char *trimmed_command = trim_whitespace(get_command_from_user);

        // check if history array needs to be expanded
        if (history_count >= history_array_size) {
            // double the size of the history array
            history_array_size += 10;
            char **temp = realloc(history_of_commands, history_array_size * sizeof(char*));
            if (temp == NULL) {
                printf("Reallocation failed\n");
                return 1;
            }
            history_of_commands = temp;  // point to the new, resized memory
        }

        // add the command to history
        history_of_commands[history_count] = malloc(strlen(get_command_from_user) + 1);
        if (history_of_commands[history_count] == NULL) {
            printf("Memory allocation for command failed\n");
            return 1;
        }

        // check if the command is empty or consists of only spaces
        if (strlen(trimmed_command) == 0) 
        {
        } 
        else {
            // accept and store the command
            strcpy(history_of_commands[history_count], trimmed_command);
            history_count++;
        }

        // print the current history
        if (strcmp(get_command_from_user, "history") == 0) 
        {
            for (int i = 0; i < history_count; i++) {
                printf("%s\n", history_of_commands[i]);
            }
        }


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
    
    for (int i = 0; i < history_count; i++) {
        free(history_of_commands[i]);
    }
    free(history_of_commands);  
    
    printf("\n");
    printf("THE SHELL HAS TERMINATED!");


    return 0;
}

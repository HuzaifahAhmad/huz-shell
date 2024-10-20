#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "header.h"

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

void print_command_history(char input_string[])
{

    char *trimmed_command = trim_whitespace(input_string);

    static int history_count = 0;
    static int history_array_size = 10;

    static char **history_of_commands = NULL;

    // Initialize history_of_commands once
    if (history_of_commands == NULL) {
        history_of_commands = malloc(history_array_size * sizeof(char*));

        if (history_of_commands == NULL) {
            printf("Memory allocation failed\n");
            return;
        }
    }
        
    // check if history array needs to be expanded
    if (history_count >= history_array_size) {
        // double the size of the history array
        history_array_size += 10;
        char **temp = realloc(history_of_commands, history_array_size * sizeof(char*));
        if (temp == NULL) {
            printf("Reallocation failed\n");
        }
        history_of_commands = temp;  // point to the new, resized memory
    }

    // add the command to history
    history_of_commands[history_count] = malloc(strlen(input_string) + 1);
    if (history_of_commands[history_count] == NULL) {
        printf("Memory allocation for command failed\n");
    }

    // check if the command is empty or consists of only spaces
    if (strlen(trimmed_command) == 0) 
    {
        return;
    } 
    else {
        // accept and store the command
    }
        strcpy(history_of_commands[history_count], trimmed_command);
        history_count++;

    // print the current history
    if (strcmp(trimmed_command, "history") == 0) 
    {
        for (int i = 0; i < history_count; i++) {
            printf("%s\n", history_of_commands[i]);
        }
    }
}
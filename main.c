#include <glob.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LIMIT 1000

char* wildcard_globbing(char inputString[MAX_LIMIT]);

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
        char *result_from_wildcard_globbing_funtion = wildcard_globbing(get_command_from_user);
        strcpy(get_command_from_user, result_from_wildcard_globbing_funtion);
        printf("%s\n", get_command_from_user);
    }

    printf("\n");
    printf("THE SHELL HAS TERMINATED!");


    return 0;
}

// checks for wildcard characters (?, *, #)
char* wildcard_globbing(char input_string[MAX_LIMIT]) 
{
    char question_mark = '?';
    char asterisk = '*';
    char delimiter[] = " ";
    char copy_input_string[MAX_LIMIT];
    char *p_tokenized_string;
    bool is_wildcard = false;
    char *ptr_copy_input_string;
    char combined_command_for_globbing[250];
    char *result_string = NULL;
    char *save_command;
    // copy input string
    strcpy(copy_input_string, input_string);

    ptr_copy_input_string = copy_input_string;
    // get first word from command
    p_tokenized_string = strtok(copy_input_string, delimiter);

    char command_word[MAX_LIMIT];
    if (p_tokenized_string != NULL)  
    {
        strncpy(command_word, p_tokenized_string, MAX_LIMIT);
        command_word[MAX_LIMIT - 1] = '\0'; // null termination
    }
    else 
    {
        return strdup(input_string);
    }

    // initialize to empty string
    result_string = malloc(1);
    if (result_string == NULL) 
    {
        printf("memory allocation failed\n");
        return NULL;
    }
    result_string[0] = '\0';



    // get the rest of words from command
    while (p_tokenized_string != NULL) 
    {
        // * - matches zero or more characters
        if (strchr(p_tokenized_string, asterisk) != NULL) 
        {
            glob_t pglob;
            int result_asterisk = glob(p_tokenized_string, 0, NULL, &pglob); // Use the pattern from user input

            // error handling for glob
            if (result_asterisk == 0) {
                // successfully matched files
                for (size_t i = 0; i < pglob.gl_pathc; i++) {

                    size_t new_len = strlen(result_string) + strlen(pglob.gl_pathv[i]) + 2; // +1 for space or null terminator
                    result_string = realloc(result_string, new_len);

                    if (result_string == NULL) {
                        printf("Memory reallocation failed\n");
                        globfree(&pglob);
                        return NULL;
                    }

                    // concatenate the file path into result_string
                    strcat(result_string, pglob.gl_pathv[i]);
                    if (i < pglob.gl_pathc - 1) {
                        strcat(result_string, " "); // add a space between file paths
                    }   
                }

                // concatenate the files with the command
                

            } else if (result_asterisk == GLOB_NOMATCH) {
                printf("%s\n", p_tokenized_string);
            } else if (result_asterisk == GLOB_ABORTED) {
                printf("Read error (permission issue) while processing the pattern: %s\n", p_tokenized_string);
            } else if (result_asterisk == GLOB_NOSPACE) {
                printf("Out of memory while processing the pattern: %s\n", p_tokenized_string);
            } else {
                printf("Unknown error occurred while processing the pattern: %s\n", p_tokenized_string);
            }

            globfree(&pglob);

            is_wildcard = true;
            break;
        }

        // ? - matches exactly one character
        if (strchr(p_tokenized_string, question_mark) != NULL) 
        {  
            glob_t pglob2;
            int result_q_mark = glob(p_tokenized_string, 0, NULL, &pglob2);

             // error handling for glob
            if (result_q_mark == 0) {
                // successfully matched files
                for (size_t i = 0; i < pglob2.gl_pathc; i++) {

                    size_t new_len = strlen(result_string) + strlen(pglob2.gl_pathv[i]) + 2; // +1 for space or null terminator
                    result_string = realloc(result_string, new_len);

                    if (result_string == NULL) {
                        printf("Memory reallocation failed\n");
                        globfree(&pglob2);
                        return NULL;
                    }

                    // concatenate the file path into result_string
                    strcat(result_string, pglob2.gl_pathv[i]);
                    if (i < pglob2.gl_pathc - 1) {
                        strcat(result_string, " "); // add a space between file paths
                    }
                }
            } else if (result_q_mark == GLOB_NOMATCH) {
                printf("%s\n", p_tokenized_string);
            } else if (result_q_mark == GLOB_ABORTED) {
                printf("Read error (permission issue) while processing the pattern: %s\n", p_tokenized_string);
            } else if (result_q_mark == GLOB_NOSPACE) {
                printf("Out of memory while processing the pattern: %s\n", p_tokenized_string);
            } else {
                printf("Unknown error occurred while processing the pattern: %s\n", p_tokenized_string);
            }

            is_wildcard = true;
            break;
        }

        // continue with the next word
        p_tokenized_string = strtok(NULL, delimiter);
    }   

    // wildcard character not present, return original
    if (!is_wildcard) 
    {
        free(result_string);
        result_string = strdup(input_string);
        return result_string;
    }

    size_t final_len = strlen(command_word) + strlen(result_string) + 2;
    char *final_result = malloc(final_len);

    if (final_result == NULL) 
    {
        printf("Memory Allocation Failed\n");
        free(result_string);
        return NULL;
    }

    if (is_wildcard)
        snprintf(final_result, final_len, "%s %s", command_word, result_string);
        // bug to fix
    free(result_string);
    
    
    return final_result;

}

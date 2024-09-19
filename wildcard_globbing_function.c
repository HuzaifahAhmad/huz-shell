#include <glob.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_LIMIT 1000


// checks for wildcard characters (?, *, #)
char* wildcard_globbing(char input_string[MAX_LIMIT]) 
{
    char delimiter[] = " ";
    char copy_input_string[MAX_LIMIT];
    char command_word[MAX_LIMIT];
    bool is_wildcard = false;
    char *p_tokenized_string;
    char *result_string = NULL;

    // Copy input string
    strcpy(copy_input_string, input_string);

    // Initialize to empty strings
    result_string = malloc(1);
    if (result_string == NULL) 
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    result_string[0] = '\0';
    command_word[0] = '\0';

    // tokenize and process the input
    p_tokenized_string = strtok(copy_input_string, delimiter);

    while (p_tokenized_string != NULL) 
    {
        // check if token contains * or ?
        if (strchr(p_tokenized_string, '*') || strchr(p_tokenized_string, '?')) {
            is_wildcard = true;
            break; // stop appending if * or ? is found
        }

        // append the token to command_word if no wildcard is found
        if (strlen(command_word) + strlen(p_tokenized_string) + 1 < MAX_LIMIT) { // +1 for space or null terminator
            if (command_word[0] != '\0') { // not the first word
                strcat(command_word, " "); // add a space before appending the next word
            }
            strcat(command_word, p_tokenized_string); // append the token to the buffer
        } else {
            printf("Buffer overflow\n");
            break;
        }

        // continue with the next token
        p_tokenized_string = strtok(NULL, delimiter);
    }   

    // if a wildcard is found, expand it using glob
    if (is_wildcard) 
    {
        glob_t pglob;
        int result_glob = glob(p_tokenized_string, 0, NULL, &pglob); // use the pattern from user input

        // rrror handling for glob
        if (result_glob == 0) { // successfully matched files
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
        } else if (result_glob == GLOB_NOMATCH) {
            printf("%s\n", p_tokenized_string);
        } else if (result_glob == GLOB_ABORTED) {
            printf("Read error (permission issue) while processing the pattern: %s\n", p_tokenized_string);
        } else if (result_glob == GLOB_NOSPACE) {
            printf("Out of memory while processing the pattern: %s\n", p_tokenized_string);
        } else {
            printf("Unknown error occurred while processing the pattern: %s\n", p_tokenized_string);
        }

        globfree(&pglob);

        // combine command_word with result_string
        size_t final_len = strlen(command_word) + strlen(result_string) + 2;
        char *final_result = malloc(final_len);
        if (final_result == NULL) 
        {
            printf("Memory Allocation Failed\n");
            free(result_string);
            return NULL;
        }

        // concatenate the command_word and the result_string
        snprintf(final_result, final_len, "%s %s", command_word, result_string);

        free(result_string);
        return final_result;
    }

    // wildcard character not present, return the original input
    free(result_string);
    return strdup(input_string);
}
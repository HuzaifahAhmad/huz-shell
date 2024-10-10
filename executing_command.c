#include <stdio.h>
#include <string.h>


#define _POSIX_SOURCE
#include <unistd.h>
#undef _POSIX_SOURCE
#include <stdio.h>


void executing_command(char **tokenized_array_for_execution) 
{
    char pwd_string[] = "pwd";
    char cwd[1024];

    for (int i = 0; tokenized_array_for_execution[i] != NULL; i++) 
    {
        if (strcmp(tokenized_array_for_execution[i], pwd_string) == 0)
        {
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);  // print current directory
            } else {
                perror("getcwd() error");  // handle error
            }
        }
     }
}
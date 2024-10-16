#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define _POSIX_SOURCE


void execute_built_in_command(char **built_in_command_execution) 
{
    char cwd[1024];

    for (int i = 0; built_in_command_execution[i] != NULL; i++) 
    {

        // pwd command implementation
        if (strcmp(built_in_command_execution[0], "pwd") == 0)
        {
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);  // print current directory
            } else {
                perror("getcwd() error");  // handle error
            }
            break;
        }


        // cd command implementation
        else if (strcmp(built_in_command_execution[0], "cd") == 0)
        {
            chdir(built_in_command_execution[i + 1]);
            printf("directory changed\n");
            break;
        }


        // echo command implementation
        else if (strcmp(built_in_command_execution[0], "echo") == 0)
        {
            for (int j = 1; built_in_command_execution[j] != NULL; j++)
            {
                printf("%s ", built_in_command_execution[j]); 
            }
            printf("\n");
            break;
        }

        // command not found implementation
        else 
        {
            printf("huz-shell: Command not found\n");
            break;
        }

     }
}
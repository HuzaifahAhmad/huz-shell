#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define _POSIX_SOURCE


void executing_command(char **tokenized_array_for_execution) 
{
    char cwd[1024];

    for (int i = 0; tokenized_array_for_execution[i] != NULL; i++) 
    {

        // pwd command implementation
        if (strcmp(tokenized_array_for_execution[0], "pwd") == 0)
        {
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);  // print current directory
            } else {
                perror("getcwd() error");  // handle error
            }
        }


        // cd command implementation
        else if (strcmp(tokenized_array_for_execution[0], "cd") == 0)
        {
            chdir(tokenized_array_for_execution[i + 1]);
            printf("directory changed\n");
            break;
        }


        // echo command implementation
        else if (strcmp(tokenized_array_for_execution[0], "echo") == 0)
        {
            for (int j = 1; tokenized_array_for_execution[j] != NULL; j++)
            {
                printf("%s ", tokenized_array_for_execution[j]); 
            }
            printf("\n");
            break;
        }


        // external command implementation
        pid_t pid, wpid;
        int status;

        pid = fork();
        if (pid == 0) {
            // child process
            if (execvp(tokenized_array_for_execution[0], tokenized_array_for_execution) == -1) {
            perror("lsh");
            }
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            // error forking
            perror("lsh");
        } else {
            // parent process
            do {
            wpid = waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }


        // command not found implementation
        // else 
        // {
        //     printf("huz-shell: Command not found\n");
        //     break;
        // }


     }
}
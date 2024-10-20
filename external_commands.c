#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


// external command implementation
bool is_input_null = false;
bool is_command_history = false;

void execute_external_command(char **external_command_execution)
{  
    if (strcmp(external_command_execution[0], "history") == 0) {
        is_command_history = true;
    }

    if (!is_command_history) 
    {
        if (external_command_execution[0] == NULL)
        {
            is_input_null = true;
            return;
        }

        if (!is_input_null) 
        {
            pid_t pid, wpid;
            int status;

            pid = fork();
            if (pid == 0) {
                // child process
                if (execvp(external_command_execution[0], external_command_execution) == -1) {
                perror("HuzShell$ ");
                }
                exit(EXIT_FAILURE);
            } else if (pid < 0) {
                // error forking
                perror("HuzShell$ ");
            } else {
                // parent process
                do {
                wpid = waitpid(pid, &status, WUNTRACED);
                } while (!WIFEXITED(status) && !WIFSIGNALED(status));
            }
        }
    }
}
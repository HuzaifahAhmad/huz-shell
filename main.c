#include <stdio.h>
#include <string.h>
#define MAX_LIMIT 30

int main() {
    char get_command_from_user[MAX_LIMIT];
    char exit[] = "exit";

    printf("START OF SHELL\n");
    
    while(1) 
    {
        printf("HuzShell$ ");
        fgets(get_command_from_user, MAX_LIMIT, stdin);
        printf("%s", get_command_from_user);

        get_command_from_user[strcspn(get_command_from_user, "\n")] = 0;

        if (strcmp(get_command_from_user, exit) == 0) {
            break;
        }
    }

    printf("\n");
    printf("THE SHELL HAS TERMINATED!");


    return 0;
}
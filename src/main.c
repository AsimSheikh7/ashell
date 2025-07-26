#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

void shell_exec()
{
    char line[MAX_LINE];
    while (1)
    {
        printf("shell> ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break; // Exit on EOF or error
        }

        // Remove trailing newline character
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // Execute the command
        int status = system(line);
        if (status == -1) {
            perror("system");
        }
    }
}

int main()
{
    shell_exec();
    return EXIT_SUCCESS;
}
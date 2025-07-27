#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 1024
#define MAX_ARGS 10

void shell_pwd()
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
    }
    else
    {
        perror("pwd");
    }
}

void shell_ls()
{
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (dir == NULL)
    {
        perror("ls");
        return;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        // Skip . and ..
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            printf("%s  ", entry->d_name);
    }
    printf("\n");
    closedir(dir);
}

void shell_cd(char *path)
{
    if (path == NULL)
    {
        fprintf(stderr, "cd: missing argument\n");
        return;
    }
    if (chdir(path) != 0)
    {
        perror("cd");
    }
}

void shell_man()
{
    printf("AShell Manual:\n");
    printf("  pwd     - Print current directory\n");
    printf("  ls      - List files in current directory\n");
    printf("  cd DIR  - Change directory to DIR\n");
    printf("  man     - Show this help manual\n");
    printf("  exit    - Exit the shell\n");
}

void shell_exec()
{
    char line[MAX_LINE];
    char *args[MAX_ARGS];

    while (1)
    {
        printf("ashell> ");
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            break; // EOF or Ctrl+D
        }

        // Remove trailing newline
        line[strcspn(line, "\n")] = '\0';

        // Tokenize input into args
        int i = 0;
        char *token = strtok(line, " ");
        while (token != NULL && i < MAX_ARGS - 1)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; // Null-terminate the array

        // Empty input
        if (args[0] == NULL)
            continue;

        // Match command
        if (strcmp(args[0], "exit") == 0)
        {
            break;
        }
        else if (strcmp(args[0], "pwd") == 0)
        {
            shell_pwd();
        }
        else if (strcmp(args[0], "ls") == 0)
        {
            shell_ls();
        }
        else if (strcmp(args[0], "cd") == 0)
        {
            shell_cd(args[1]);
        }
        else if (strcmp(args[0], "man") == 0)
        {
            shell_man();
        }
        else
        {
            // Try to run any external command
            pid_t pid = fork();
            if (pid == 0)
            {
                execvp(args[0], args);
                perror("exec");
                exit(EXIT_FAILURE);
            }
            else if (pid > 0)
            {
                int status;
                wait(&status);
            }
            else
            {
                perror("fork");
            }
        }
    }
}

int main()
{
    shell_exec();
    return EXIT_SUCCESS;
}

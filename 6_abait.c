#include "main.h"

/**
 * _getline - Read a line of input from stdin
 *
 * Return: A pointer to the line read, or NULL if an error occurred
 */
char *_getline(void)
{
    static char buffer[1024];
    static int pos;
    int c;

    while (1)
    {
        c = getchar();

        if (c == EOF || c == '\n')
        {
            buffer[pos] = '\0';
            pos = 0;
            return (buffer);
        }
        else
        {
            buffer[pos] = c;
            pos++;
        }

        if (pos >= 1024)
        {
            buffer[pos] = '\0';
            pos = 0;
            return (buffer);
        }
    }
}

/**
 * main - Entry point
 *
 * Return: Always 0
 */
int main(void)
{
    char *line;
    char **args;
    int status;

    do {
        printf("$ ");
        line = _getline();
        args = split_line(line);
        status = execute(args);

        free(line);
        free(args);
    } while (status);

    return (0);
}

/**
 * execute - Execute a command
 * @args: An array of strings containing the command and its arguments
 *
 * Return: 1 if the shell should continue running, 0 if it should exit
 */
int execute(char **args)
{
    if (args[0] == NULL)
    {
        return (1);
    }
    else if (_strcmp(args[0], "exit") == 0)
    {
        return (0);
    }
    else if (_strcmp(args[0], "env") == 0)
    {
        int i;
        extern char **environ;

        for (i = 0; environ[i] != NULL; i++)
        {
            printf("%s\n", environ[i]);
        }

        return (1);
    }
    else
    {
        pid_t pid;
        int status;

        pid = fork();
        if (pid == 0)
        {
            if (execve(args[0], args, NULL) == -1)
            {
                perror("Error");
            }
            exit(EXIT_FAILURE);
        }
        else if (pid < 0)
        {
            perror("Error");
        }
        else
        {
            do {
                waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }

    return (1);
}


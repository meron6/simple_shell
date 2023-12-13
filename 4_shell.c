#include "holberton.h"

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

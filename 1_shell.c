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

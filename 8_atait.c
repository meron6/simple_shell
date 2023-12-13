#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void) {
    char buffer[BUFFER_SIZE];
    char *args[100]; // Adjust this size based on your needs
    int status;
    
    while (1) {
        printf("$ "); // Displaying the prompt
        fgets(buffer, BUFFER_SIZE, stdin); // Reading the command line
        
        // Parsing the command line into arguments
        int i = 0;
        args[i] = strtok(buffer, " \n"); // Tokenize the command line
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " \n");
        }
        args[i] = NULL; // Null-terminate the argument list
        
        // Check if the command is "exit" and has an argument
        if (strcmp(args[0], "exit") == 0 && args[1] != NULL) {
            status = atoi(args[1]); // Convert the argument to an integer
            exit(status); // Exit the shell with the specified status
        }
        
        // Forking a child process
        pid_t pid = fork();
        
        if (pid == -1) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process executes the command
            if (execvp(args[0], args) == -1) {
                perror("Execution failed");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process waits for the child to complete
            waitpid(pid, &status, 0);
        }
    }
    return 0;
}

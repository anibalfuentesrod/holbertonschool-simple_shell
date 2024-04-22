#include "shell.h"
/**
 * display_prompt - this just simply display the prompt
**/
void display_prompt(void)
{
		printf("$ ");
		fflush(stdout);	
}
/**
 * remove_newline - this obv remove the newline character from a string
 * @str: The string to modify
**/
void remove_newline(char *str)
{
	char *newline = strchr(str, '\n');
	
	if (newline != NULL)
	{
		*newline = '\0';
	}
}
/**
 * execute_command - this executes the command that you put on it
 * @command: the command to execute bruhh
**/
void execute_command(char *command)
{
	pid_t pid = fork();
	int status, i;
	char *token;

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0)
	{
		char *args[MAX_COMMAND_LENGTH];

		token = strtok(command, " ");
		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;

		execvp(args[0], args);

		perror(args[0]);
		exit(EXIT_FAILURE);
	} else {
		waitpid(pid, &status, 0);
	}
}

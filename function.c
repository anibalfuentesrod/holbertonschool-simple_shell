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
		newline = '\0';
	}
}
/**
 * execute_command - this executes the command that you put on it
 * @command: the command to execute bruhh
**/
int execute_command(char *command)
{
	pid_t pid = fork();
	int status = 0;
	int i = 0;
	char *token;
	char *args[MAX_COMMAND_LENGTH];

	token = strtok(command, " ");
	while (token != NULL)
	{
		args[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;
	if (pid < 0)
	{
		perror("fork");
		free(command);
		exit(EXIT_FAILURE);
	} else if (pid == 0) /*Child Process HERE*/
	{
		if (execvp(args[0], args) < 0)
		{
			perror(args[0]);
			free(command);
			exit(2);
		} 
	} else {
		waitpid(pid, &status, 0);
	}
	return (status);
}

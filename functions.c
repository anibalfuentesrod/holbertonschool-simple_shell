#include "shell.h"
/**
 * is_interactive_mode - this check if shell is running interactive or not
 *
 * Return: true if running is interactive mode, false if not
**/
bool is_interactive_mode(void)
{
	return (isatty(STDIN_FILENO));
}
/**
 * display_prompt - this just simply display the prompt
**/
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		printf("$ ");
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
	int status;

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char *args[MAX_COMMAND_LENGTH];

		args[0] = strtok(command, "");
		if (args[0] == NULL)
			exit(EXIT_SUCCESS);

		execvp(args[0], args);
		perror(args[0]);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

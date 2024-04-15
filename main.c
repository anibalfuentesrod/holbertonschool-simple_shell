#include "shell.h"
/**
 * main - the main duhh
 * @args: argument
 * @argv: argument vector
 * Return: 0
**/
int main (void)
{
	char command[MAX_COMMAND_LENGTH];
	bool interactive_mode = is_interactive_mode();
	printf("You're now in my shell...\n");

	/* Check is rnning interactively if it is then...*/
	if (interactive_mode)
	{
		printf("Shell is running interactively\n");
	}
	else
	{
		printf("Shell is running non-interactively\n");
	}
	/* Main shell loop..*/
	while (1)
	{
		/* This part displays prompt if running interactively */
		if (interactive_mode)
		{
			display_prompt();
			/* Reads the user input */
			if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
			{
				printf("\n");
				break;
			}
			remove_newline(command);
		} else {
			/* Read input if not running interactively */
			if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
			{
				break;
			}
			remove_newline(command);
		}
		if (strlen(command) == 0)
		{
			continue;
		}
		/* Checks for exit command */
		if (strcmp(command, "exit") == 0)
		{
			break;
		}
		/* Execute commands */
		execute_command(command);
	}
	printf("You just exited the shell...\n");

	return (0);
}

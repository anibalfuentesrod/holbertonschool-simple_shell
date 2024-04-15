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

	if (interactive_mode)
	{
		printf("Shell is running interactively\n");
	}
	else
	{
		printf("Shell is running non-interactively\n");
	}

	while (1)
	{
		if (interactive_mode)
		{
			display_prompt();
			if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
			{
				printf("\n");
				break;
			}
			remove_newline(command);
		} else {
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
		if (strcmp(command, "exit") == 0)
		{
			break;
		}
		execute_command(command);
	}
	printf("You just exited the shell...\n");

	return (0);
}

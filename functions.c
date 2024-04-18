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
	if (is_interactive_mode())
	{
		/* Check if running interactively */
		printf("($) ");
		fflush(stdout);
	}
}
/**
 * remove_newline - this obv remove the newline character from a string
 * @str: The string to modify
**/
void remove_newline(char *str)
{
	str[strcspn(str, "\n")] = '\0';
}
/**
 * execute_command - this executes the command that you put on it
 * @command: the command to execute bruhh
**/
void execute_command(char *command)
{
	pid_t pid = fork();
	int status;
	int i;

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		char *args[MAX_COMMAND_LENGTH];

		args[0] = strtok(command, " ");
		i = 1;

		while ((args[i] = strtok(NULL, " ")) != NULL)
		{
			i++;
		}
		execvp(args[0], args);
		
		fprintf(stderr, "./hsh: %s: ", args[0]);
		perror("");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

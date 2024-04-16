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
		printf("(　-_･) ︻デ═一 ▸ ");
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
	int i;
	/* Fork proccess to execute command */
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

		/* Tokenize command */
		while ((args[i] = strtok(NULL, " ")) != NULL)
		{
			i++;
		}
		/* Execute command */
		execvp(args[0], args);
		/* Handle command not found */
		fprintf(stderr, "./hsh: %s: command not found\n", command);
		exit(EXIT_FAILURE);
	} else
	{
	/* Wait for child procces to finish */
	int status;

	waitpid(pid, &status, 0);
	}
}

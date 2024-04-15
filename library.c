#include "shell.h"
/**
 * is_interactive_mode - this check if shell is running interactive or not
 *
 * Return: true if running is interactive mode, false if not
**/
bool is_interactive_mode()
{
	return isatty(STDIN_FILENO);
}
/**
 * display_prompt - this just simply display the prompt
**/
void display_prompt()
{
	if (is_interactive_mode())
	{
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
		fprintf(stderr, "./hsh: %s: command not found\n", command);
		exit(EXIT_FAILURE);
	} else {
	
	int status;
	waitpid(pid, &status, 0);
	}
}

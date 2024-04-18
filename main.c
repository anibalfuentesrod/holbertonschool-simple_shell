#include "shell.h"
/**
 * initialize_shell - initializes the shell and displays a my welcome message
*/

void initialize_shell(void)
{

	if (is_interactive_mode())
	{
		printf("Shell is running interactively\n");
	}
}

/**
 * read_command - reads a command from the user input.
 * @command: pointer to the buffer where the command will be stored.
**/
void read_command(char *command)
{
	ssize_t bytes_read = read(STDIN_FILENO, command, MAX_COMMAND_LENGTH);
	
	if (bytes_read == -1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	else if (bytes_read == 0)
	{
		if (is_interactive_mode())
		{
		printf("\n");
		}
		exit(EXIT_SUCCESS);
	}
	command[bytes_read - 1] = '\0';
}
/**
 * proccess_command - processes the command entered by the user.
 * @command: the command to procces.
**/
void proccess_command(char *command)
{
	if (strlen(command) == 0)
	{
		return;
	}

	if (strcmp(command, "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	execute_command(command);
}
/**
 * main - the main function of the shell program,
 * controls the main loop of the shell,
 * searching for command, reading input,
 * and executing the commands :)
 *
 * Return: 0 on success.
**/
int main()
{
	char command[MAX_COMMAND_LENGTH];

	initialize_shell();

	while (1)
	{
		display_prompt();
		read_command(command);
		proccess_command(command);
	}
	return (0);
}

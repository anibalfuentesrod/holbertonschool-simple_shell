#include "shell.h"
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
		printf("\n");
		exit(EXIT_SUCCESS);
	}
	remove_newline(command);
}
/**
 * proccess_command - processes the command entered by the user.
 * @command: the command to procces.
**/
void proccess_command(char *command)
{
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
	char input[MAX_COMMAND_LENGTH];
	char *token;

	while (1)
	{

		display_prompt();

		read_command(input);

		token = strtok(input, "\n");
		while (token != NULL)
		{
			if (strcmp(token, "exit") == 0)
			{
				exit(EXIT_FAILURE);
			}
			else{
				execute_command(token);
			}
			token = strtok(NULL, "\n");
		}

	}
	return (0);
}

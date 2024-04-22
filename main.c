#include "shell.h"
/**
 * read_command - reads a command from the user input.
 * @command: pointer to the buffer where the command will be stored.
**/
char *read_command()
{
	char *cmd = NULL;
	size_t len = 0;
	ssize_t bytes_read;
	
	display_prompt();
	bytes_read = getline(&cmd, &len, stdin);
	if (bytes_read == -1 && !isatty(STDIN_FILENO))
	{
		exit(EXIT_FAILURE);
	}
	remove_newline(cmd);
	return (cmd);
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
	char *token, *cmd = NULL;

	while (1)
	{

		cmd = read_command();

		token = strtok(cmd, "\n");
		while (token != NULL)
		{
			if (strcmp(token, "exit") == 0)
			{
				exit(EXIT_SUCCESS);
			}
			else{
				execute_command(token);
			}
			token = strtok(NULL, "\n");
		}

	}
	return (0);
}

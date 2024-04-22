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
	
	if (isatty(STDIN_FILENO))
	{
		display_prompt();
	}
	bytes_read = getline(&cmd, &len, stdin);
	if (bytes_read == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			perror("getline");
			free(cmd);
			return(NULL);
		}
		free(cmd);
		exit(EXIT_SUCCESS);
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
	int status = 0;

	while (1)
	{

		cmd = read_command();

		token = strtok(cmd, "\n");
		while (token != NULL && cmd != NULL)
		{
			if (strcmp(token, "exit") == 0)
			{
				free(cmd);
				exit(EXIT_SUCCESS);
			}
			else{
				status = execute_command(token);
			}
			token = strtok(NULL, "\n");
		}

	}
	return (status);
}

#include "shell.h"
/**
 * remove_whitespace - remove the withespace in the command
 * @cmd: comand to remove the shitespace
**/
int remove_whitespace(char *cmd)
{
	int i;

	for (i = 0; cmd[i] != '\0'; i++)
	{
		if (cmd[i] != ' ')
		{
			if (cmd[i] == '\0')
			{
				return (1);
			}
			else
			{
				return (0);
			}
		}
	}
	return (1);
}


/**
 * read_command - reads a command from the user input.
 *
 * Return: cmd
**/
char *read_command(void)
{
	char *cmd = NULL;
	size_t len = 0, size = 0;
	ssize_t bytes_read;


	if (isatty(STDIN_FILENO))
	{
		display_prompt();
	}
	bytes_read = getline(&cmd, &size, stdin);
	if (bytes_read == -1)
	{
		if (isatty(STDIN_FILENO))
		{
			perror("getline");
			return (NULL);
		}
		free(cmd);
		exit(EXIT_SUCCESS);
	}
	len = strlen(cmd);

	if (len > 0 && cmd[len - 1] == '\n')
	{
		cmd[len - 1] = '\0';
	}
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
int main(void)
{
	char *token, *cmd = NULL;
	int status = 0;
	int check = 1;

	while (1)
	{
		while (check == 1)
		{
			cmd = read_command();
			check = remove_whitespace(cmd);

			if (check == 1 || cmd == NULL)
			{
				free(cmd);
			}
		}
		token = strtok(cmd, "\n");

		if (token != NULL && cmd != NULL)
		{
			if (strcmp(token, "exit") == 0)
			{
				free(cmd);
				exit(EXIT_SUCCESS);
			}
			else
			{
				status = execute_command(token);
			}
			token = strtok(NULL, "\n");
		}
		free(cmd);
		check = 1;
	}
	return (status);
}

#include "shell.h"
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

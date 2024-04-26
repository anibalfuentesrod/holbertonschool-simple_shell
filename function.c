#include "shell.h"
/**
 * display_prompt - this just simply display the prompt
**/
void display_prompt(void)
{
	printf("$ ");
	fflush(stdout);
}
/**
 * remove_newline - this obv remove the newline character from a string
 * @str: The string to modify
**/
void remove_newline(char *str)
{
	char *newline = strchr(str, '\n');

	if (newline != NULL)
	{
		newline = '\0';
	}
}
/**
 * execute_command - this executes the command that you put on it
 * @command: the command to execute bruhh
 *
 * Return: status
**/
int execute_command(char *command)
{
	pid_t pid = fork();
	int status = 0;
	int i = 0;
	char *token;
	char *args[MAX_COMMAND_LENGTH];

	token = strtok(command, " ");
	while (token != NULL)
	{
		args[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;
	if (pid < 0)
	{
		perror("fork");
		free(command);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) /*Child Process HERE*/
	{
		if (execvp(args[0], args) < 0)
		{
			perror(args[0]);
			free(command);
			exit(2);
		}
	} else
	{
		waitpid(pid, &status, 0);
	}
	return (status);
}
/**
 * remove_whitespace - remove the withespace in the command
 * @cmd: command to remove the space
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
 * read_command - reads a command from the user input
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

	if (len > 0 && cmd[len -1] == '\n')
	{
		cmd[len - 1] = '\0';
	}
	return (cmd);
}

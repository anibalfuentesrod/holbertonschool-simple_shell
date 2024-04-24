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
		*newline = '\0';
	}
}

/**
 *add_bin - adds command line
 *@cmd: comand pointer in use
 *Return: cmd
 */
char *add_bin(char *cmd)
{
	char temp[] = "/bin/";
	int i;
	int j;
	bool flag = false;
	char *new_mem;

	for (i = 0; temp[i] != '\0'; i++)
	{
		if (temp[i] != cmd[i])
		{
			flag = true;
			break;
		}
	}
	if (flag)
	{
	new_mem = malloc(strlen(temp) + strlen(cmd) + 1);
		for (i = 0; temp[i] != '\0'; i++)
		{
			new_mem[i] = temp[i];
		}
		for (j = 0; cmd[j] != '\0'; j++, i++)
		{
			new_mem[i] = cmd[j];
		}
		new_mem[i] = '\0';
		return (new_mem);
	}
	return (NULL);
}
/**
 * execute_command - this executes the command that you put on it
 * @command: the command to execute bruhh
 * 
 * Return: status of the child process
**/
int execute_command(char *command)
{
	pid_t pid = fork();
	int status = 0;
	int i = 0;
	char *token;
	char *args[MAX_COMMAND_LENGTH];
	char *cmd = NULL;

	token = strtok(command, " ");
	cmd = add_bin(token);
	while (token != NULL)
	{
		args[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;
	if (cmd != NULL)
		args[0] = cmd;
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) /*Child Process HERE*/
	{
		if (execve(args[0], args, NULL) < 0)
		{
			perror(args[0]);
			exit(2);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	free(cmd);
	return (status);
}


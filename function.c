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
 *
 *
 *
 *
 *
 */
char *check_path(char *cmd, char *envp[])
{
	char *path;
	char *token, *path_cpy = NULL, *temp;
	int i;
	
	path = NULL;
	for (i = 0; envp[i] != NULL; i++)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break;
		}
	}
	if (cmd == NULL)
		return (NULL);
	if (strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));
		else
			return (NULL);
	}
	for (i = 0; envp[i] != NULL; i++)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5;
			break;
		}
	}
	if (path == NULL || *path == '\0')
		return (NULL);

	path_cpy = strdup(path);
	if (path_cpy == NULL)
		exit(EXIT_FAILURE);

	token = strtok(path_cpy, ":");
	while (token != NULL)
	{
		temp = malloc(PATH_MAX);
		if (temp == NULL)
			return (NULL);
		snprintf(temp, PATH_MAX, "%s/%s", token, cmd);
		if (access(temp, X_OK) == 0)
		{
			free(path_cpy);
			return (temp);
		}
		free(temp);
		token = strtok(NULL, ":");
	}
	free(path_cpy);
	return (NULL);
}

/**
 * execute_command - this executes the command that you put on it
 * @command: the command to execute bruhh
 * @envp: enviromental value
 *
 * Return: status of the child process
**/
int execute_command(char *command, char *envp[])
{
	pid_t pid = fork();
	int status = 0;
	int i = 0;
	char *token;
	char *args[MAX_COMMAND_LENGTH];
	char *cmd = NULL;

	token = strtok(command, " ");
	while (token != NULL)
	{
		args[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;
	cmd = check_path(args[0], envp);
	if (cmd == NULL)
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		free(command);
		exit(127);
	}
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) /*Child Process HERE*/
	{
		if (execve(cmd, args, envp) < 0)
		{
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	free(cmd);
	return (status);
}


#include "shell.h"
/**
 * remove_newline - this removes the new line at $ or command??
**/
void remove_newline(char *str)
{
	int len = strlen(str);

	if (str[len - 1] == '\n')
	{
		str[len - 1] = '\0';
	}
}
/**
 * main - simple practice of what a simle shell should be
 *
 * Return: 0 un succes
**/

int main()
{
	char command[MAX_COMMAND_LENGTH];
	bool first_command = true;
	int status;
	pid_t pid;

	while(1)
	{
		printf("$ ");
		fflush(stdout);

		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			else
			{
				perror("fgets");
				exit(EXIT_FAILURE);
			}
		}
		remove_newline(command);

		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execlp(command, command, NULL) == -1)
			{
				fprintf(stderr, "Error: command not found: %s\n", command);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			waitpid(pid, &status, 0);
			
			if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			{
				if (!first_command)
				{
					printf("\n");
				}
				first_command = false;
			}
		}
	}
	return (0);
}

#include "shell.h"
/**
 * main - simple practice of what a simle shell should be
 *
 * Return: 0 un succes
**/

int main()
{
	char command[MAX_COMMAND_LENGTH];

	while(1)
	{
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
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
		command[strcspn(command, "\n")] = '\0';

		if (execlp(command, command, NULL) == -1)
		{
			fprintf(stderr, "Error: command not found: %s\n", command);
			exit(EXIT_FAILURE);
		}
		}
		else
		{
			wait(NULL);
		}
	}
	return (0);
}

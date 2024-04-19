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

		fprintf(stderr,"Error: command not found: %s\n", command);
		}
	}
	return (0);
}

#include "library.h"
/**
 * display_prompt - display the prompt duhhhh
**/
void display_prompt()
{
	printf("#cisfun$ ");
	fflush(stdout);
}
/**
 * main - the main
 *
 * Return: 0
**/
int main()
{
	char command[MAX_COMMAND_LENGTH];
	pid_t pid = fork();
	int i;

	while (1)
	{
		display_prompt();

		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		command[strcspn(command, "\n")] = '\0';

		if (strlen(command) == 0)
		{
			continue;
		}
		
		if (strcmp(command, "exit") == 0)
		{
			break;
		}
		pid = fork();
		
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		} else if (pid == 0)
		{
			char *args[MAX_COMMAND_LENGTH];
			args[0] = strtok(command, " ");
			i = 1;
			while ((args[i] = strtok(NULL, " ")) != NULL)
			{
				i++;
			}
			execvp(args[0], args);

			fprintf(stderr, "./hsh: %s: command not found\n", command);
			exit(EXIT_FAILURE);
			
		} else 
		{
			int status;
			waitpid(pid, &status, 0);
		}
	}
	return (0);
}

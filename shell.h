#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_COMMAND_LENGTH 1000

void display_prompt(void);
void remove_newline(char *str);
int execute_command(char *command, char *envp[]);


#endif

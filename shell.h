#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

#define MAX_COMMAND_LENGTH 1000

bool is_interactive_mode(void);
void display_prompt(void);
void remove_newline(char *str);
int execute_command(char *command);


#endif

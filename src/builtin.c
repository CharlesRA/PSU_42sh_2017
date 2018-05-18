/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** builtins
*/

#include <unistd.h>
#include <sys/wait.h>
#include "minishell.h"
#include "commands.h"

int check_builtin(command_t *command)
{
	char *str[] = {"cd", "env", "setenv", "unsetenv", "exit", NULL};
	int (*function[])(command_t *command) =
		{&cmd_cd, &cmd_env, &cmd_setenv, &cmd_unsetenv, &cmd_exit};

	for (int i = 0 ; str[i] ; i++)
		if (my_strcmp(command->node->data[0], str[i]) == 0) {
			command->ret = function[i](command);
			return (0);
		}
	return (1);
}

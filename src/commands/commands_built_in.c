/*
** EPITECH PROJECT, 2018
** commands
** File description:
** regroups all minishell built-in commands
*/

#include <stdio.h>
#include <unistd.h>
#include "commands.h"

int cmd_cd(command_t *command)
{
	return (do_cd(command->node->data[1], command));
}

int cmd_env(command_t *command)
{
	return (display_env(command));
}

int cmd_setenv(command_t *command)
{
	int len = my_tablen(command->node->data);

	if (len == 1) {
		display_env(command);
		command->ret = 0;
	} else if (len > 3) {
		my_puterror("setenv: Too many arguments.\n");
		command->ret = 1;
	} else
		change_env(command, &(command->node->data[1]), 0);
	return (0);
}

int cmd_unsetenv(command_t *command)
{
	int len = my_tablen(command->node->data);

	if (len > 2) {
		my_puterror("unsetenv: Too many arguments.\n");
		command->ret = 1;
	} else if (len < 1) {
		my_puterror("unsetenv: Too few arguments.\n");
		command->ret = 1;
	} else
		change_env(command, &(command->node->data[1]), 1);
	return (0);
}

int cmd_exit(command_t *command)
{
	if (command->node->data[1]) {
		if (command->node->data[2]) {
			my_puterror("exit: Expression Syntax.\n");
			command->ret = 1;
			return (0);
		}
		command->ret = my_getnbr(command->node->data[1]);
	}
	destroy_tab(command->node->data);
	destroy_tab(command->env);
	exit_shell(command->ret);
	return (0);
}

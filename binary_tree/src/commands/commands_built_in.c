/*
** EPITECH PROJECT, 2018
** commands
** File description:
** regroups all minishell built-in commands
*/

#include <stdio.h>
#include <unistd.h>
#include "commands.h"

int cmd_cd(char **cmd, command_t *command)
{
	do_cd(cmd[1], command);
	destroy_tab(cmd);
	return (0);
}

int cmd_env(char **cmd, command_t *command)
{
	char **tmp = my_tabdup(command->env);
	int i = 1;

	tmp = check_env_arguments(&cmd[1], tmp, &i);
	if (cmd[i] == NULL)
		display_env(tmp);
	else
		command->ret = launch_program(&cmd[i], tmp);
	destroy_tab(tmp);
	destroy_tab(cmd);
	return (0);
}

int cmd_setenv(char **cmd, command_t *command)
{
	int len = my_tablen(cmd);

	if (len == 1) {
		display_env(command->env);
		command->ret = 0;
	} else if (len > 3) {
		my_puterror("setenv: Too many arguments.\n");
		command->ret = 1;
	} else
		change_env(command, &cmd[1], 0);
	return (0);
}

int cmd_unsetenv(char **cmd, command_t *command)
{
	int len = my_tablen(cmd);

	if (len > 2) {
		my_puterror("unsetenv: Too many arguments.\n");
		command->ret = 1;
	} else if (len < 1) {
		my_puterror("unsetenv: Too few arguments.\n");
		command->ret = 1;
	} else
		change_env(command, &cmd[1], 1);
	return (0);
}

int cmd_exit(char **cmd, command_t *command)
{
	if (cmd[1]) {
		if (cmd[2]) {
			my_puterror("exit: Expression Syntax.\n");
			command->ret = 1;
			return (0);
		}
		command->ret = my_getnbr(cmd[1]);
	}
	destroy_tab(cmd);
	destroy_tab(command->env);
	exit_shell(command->ret);
	return (0);
}

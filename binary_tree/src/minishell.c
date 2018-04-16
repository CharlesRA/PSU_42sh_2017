/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** core function of minishell
*/

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "minishell.h"
#include "commands.h"

static int check_sh_cmd(char **cmd, command_t *command)
{
	char *str[] = {"cd", "env", "setenv", "unsetenv", "exit"};
	int (*function[])(char **cmd, command_t *command) =
		{&cmd_cd, &cmd_env, &cmd_setenv, &cmd_unsetenv, &cmd_exit};

	for (int i = 0 ; i < 5 ; i++)
		if (my_strcmp(cmd[0], str[i]) == 0) {
			function[i](cmd, command);
			return (0);
		}
	return (1);
}

int execute_command(command_t *command)
{
	char **cmd = my_str_to_word_array(command->node->data, " \t");

	if (cmd == NULL)
		return (1);
	if (check_sh_cmd(cmd, command) == 0)
		return (0);
	command->ret = launch_program(cmd, command->env);
	destroy_tab(cmd);
	return (0);
}

int check_node(command_t *command)
{
	command_t tmp = {command->node->left, command->env, command->ret};

	if (command->node->type == SEMICOLON) {
		check_node(&tmp);
		command->node = command->node->right;
		check_node(command);
	} else {
		execute_command(command);
	}
	return (0);
}

int make_commands(command_t *command)
{
	if (command->node == NULL || command->node->right == NULL)
		return (1);
	command->node = command->node->right;
	check_node(command);
	return (0);
}

int minishell(char **env)
{
	command_t command = {NULL, my_tabdup(env), 0};

	while (1) {
		if (prompt(&command) == 1)
			return (1);
		make_commands(&command);
		destroy_nodes(command.node);
	}
	destroy_tab(command.env);
	return (command.ret);
}

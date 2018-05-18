/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** core function of minishell
*/

#include "minishell.h"
#include "commands.h"

static void separator_node(command_t *command)
{
	command_t left = {command->node->left, command->env, command->output,
			command->input, command->ret};
	command_t right = {command->node->right, command->env, command->output,
			command->input, command->ret};

	check_node(&left);
	if (command->node->type == SEMICOLON ||
	(command->node->type == OR && left.ret != 0) ||
	(command->node->type == AND && left.ret == 0)) {
		check_node(&right);
		command->ret = right.ret;
	} else {
		command->ret = left.ret;
	}
}

void redirect_or_pipe_node(command_t *command)
{
	command_t left = {command->node->left, command->env, command->output,
			command->input, command->ret};
	command_t right = {command->node->right, command->env, command->output,
			command->input, command->ret};

	if (command->node->type == PIPE)
		pipe_node(command, &left, &right);
	else {
		if (command->node->type == ONE_RIGHT_BRACKET ||
		command->node->type == TWO_RIGHT_BRACKET)
			left.output = get_output(right.node,
						command->node->type);
		else
			left.input = get_input(right.node, command->node->type);
		check_node(&left);
		command->ret = left.ret;
		close_input_output(&left);
	}
}

int check_node(command_t *command)
{
	if (command->node == NULL || command->node->type == UNKNOWN)
		return (1);
	if (command->node->type == SEMICOLON ||
	command->node->type == OR || command->node->type == AND) {
		separator_node(command);
	} else if (command->node->type == ONE_LEFT_BRACKET ||
		command->node->type == TWO_LEFT_BRACKET ||
		command->node->type == ONE_RIGHT_BRACKET ||
		command->node->type == TWO_RIGHT_BRACKET ||
		command->node->type == PIPE) {
		redirect_or_pipe_node(command);
	} else
		return (execute_command(command));
	return (0);
}

static int make_commands(command_t *command)
{
	node_t *root = command->node;

	if (command->node == NULL || command->node->right == NULL)
		return (1);
	if (command->node->type == 0)
		return (0);
	command->node = command->node->right;
	check_node(command);
	destroy_nodes(root);
	return (0);
}

int minishell(char **env)
{
	command_t command = {NULL, my_tabdup(env), 1, 0, 0};

	while (1) {
		if (prompt(&command) == 1)
			return (1);
		make_commands(&command);
	}
	destroy_tab(command.env);
	return (command.ret);
}

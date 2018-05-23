/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** handles pipes
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "minishell.h"

void pipe_node(command_t *command)
{
	int nb_wait = 1;
	int ret = 0;
	command_t execute = {NULL, command->env, command->output,
			command->input, command->fd_tmp,
			{command->pipe_fd[0], command->pipe_fd[1]}, command->ret};

	while (command->node->left->type != COMMAND)
		command->node = command->node->left;
	pipe(execute.pipe_fd);
	execute.node = command->node->left;
	execute_command(&execute);
	for ( ; command->node->type == PIPE ; nb_wait++) {
		execute.node = command->node->right;
		close(execute.pipe_fd[1]);
		execute.fd_tmp = execute.pipe_fd[0];
		if (pipe(execute.pipe_fd) == -1)
			return;
		execute_command(&execute);
		command->node = command->node->parent;
	}
	while (nb_wait--)
		wait(&ret);
	command->ret = check_signal(ret);
}

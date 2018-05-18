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

void pipe_node(command_t *command, command_t *left, command_t *right)
{
	int pipe_fd[2];
	pid_t child_l;
	pid_t child_r;

	get_command_line(right);
	if (left->node->type == COMMAND)
		get_command_line(left);
	if (pipe(pipe_fd) == -1) {
		my_perror("pipe");
		return;
	}
	child_l = fork();
	if (child_l == 0) {
		dup2(pipe_fd[1], command->output);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execve(left->node->data[0], left->node->data, command->env);
	}
	child_r = fork();
	if (child_r == 0) {
		dup2(pipe_fd[0], command->input);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execve(right->node->data[0], right->node->data, command->env);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(child_r, NULL, 0);
}

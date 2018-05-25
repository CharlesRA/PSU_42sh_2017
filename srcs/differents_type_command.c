/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** differents_type_command.c
*/

#include <unistd.h>
#include <stdlib.h>
#include "shell.h"
#include "bultin.h"

int get_index(int i, int change)
{
	static int index = 0;

	if (change == 1)
		index = i;
	return (index);
}

int case_real_command(int *pipe_fd, shell_t *new,
char *command, char **envp)
{
	int i = get_index(0, 0);

	operator_pipe_redirect_file(new, i, pipe_fd, new->path);
	if (check_builtin(new, command) == 1) {
		apply_builtin(command, new, envp);
		exit(0);
	}
	if (execve(command, *new->different_command, envp) == -1) {
		error_execve(command);
		exit(1);
	}
	return (0);
}

int case_builtin(int *proc, shell_t *new, char **envp)
{
	wait_process(proc, new);
	apply_builtin(new->command, new, envp);
	return (0);
}

int case_fork(int temp, int *pipe_fd, shell_t *new, char **envp)
{
	pid_t pid = 0;
	int i = get_index(0, 0);

	if (temp != -1)
		close(pipe_fd[1]);
	temp = pipe_fd[0];
	if (pipe(pipe_fd) == -1)
		return (84);
	pid = fork();
	if (pid == 0) {
		dup2(temp, 0);
		case_real_command(pipe_fd, new, new->command, envp);
	} else if (pid == -1)
		return (84);
	return (temp);
}

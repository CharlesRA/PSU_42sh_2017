/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** differents_type_command.c
*/

#include "shell.h"
#include "builtin.h"

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
	if (check_builtin(command) == 1) {
		apply_builtin(command, new, envp);
		exit(EXIT_NORMAL);
	}
	if (execve(command, *new->different_command, envp) == -1) {
		error_execve(command);
		exit(1);
	}
	return (EXIT_NORMAL);
}

int case_builtin(int *proc, shell_t *new, char **envp)
{
	wait_process(proc, new);
	apply_builtin(new->command, new, envp);
	return (EXIT_NORMAL);
}

int case_fork(int temp, int *pipe_fd, shell_t *new, char **envp)
{
	pid_t pid = 0;

	if (temp != -1)
		close(pipe_fd[1]);
	temp = pipe_fd[0];
	if (pipe(pipe_fd) == -1)
		return (EXIT_FAIL);
	pid = fork();
	if (pid == 0) {
		dup2(temp, 0);
		case_real_command(pipe_fd, new, new->command, envp);
	} else if (pid == -1)
		return (EXIT_FAIL);
	return (temp);
}

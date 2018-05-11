/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** differents_type_command.c
*/

#include <unistd.h>
#include <stdlib.h>
#include "shell.h"
#include "builtins.h"

int get_index(int i, int change)
{
	static int index = 0;

	if (change == 1)
		index = i;
	return (index);
}

int case_real_command(int *pipe_fd, shell_t *tcsh,
char *command, char **envp)
{
	int i = 0;

	i = get_index(i, 0);
	operator_pipe_redirect_file(tcsh,i, pipe_fd, tcsh->path);
	if (check_builtin(tcsh,command) == 1) {
		apply_builtin(command, tcsh,envp);
		exit(0);
	}
	if (execve(command, *tcsh->different_command, envp) == -1) {
		error_execve(command);
		exit(1);
	}
	return (0);
}

int case_builtin(int *proc, shell_t *tcsh, char **envp, char ***skip)
{
	wait_process(proc, tcsh,skip);
	apply_builtin(tcsh->command, tcsh,envp);
	skip = tcsh->different_command;
	return (0);
}

int case_fork(int temp, int *pipe_fd, shell_t *tcsh, char **envp)
{
	pid_t pid = 0;
	int i = 0;

	i = get_index(i, 0);
	if (temp != -1)
		close(pipe_fd[1]);
	temp = pipe_fd[0];
	if (pipe(pipe_fd) == -1 || (pid = fork()) == -1)
		return (84);
	if (pid == 0) {
		dup2(temp, 0);
		case_real_command(pipe_fd, tcsh, tcsh->command, envp);
	}
	return (temp);
}

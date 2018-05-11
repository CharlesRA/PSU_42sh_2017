/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** operator.c
*/

#include "shell.h"
#include "str.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

char *check_redirection(shell_t *tcsh, int *i)
{
	char *str = NULL;
	int fd = 0;

	if ((tcsh->priority[*i + 1] == ONE_RIGHT
	|| tcsh->priority[*i + 1] == TWO_RIGHT
	|| tcsh->priority[*i + 1] == ONE_LEFT
	|| tcsh->priority[*i + 1] == TWO_LEFT)
	&& *tcsh->different_command[1] != NULL)
		str = *tcsh->different_command[1];
	return (str);
}

int skip_redirection(shell_t *tcsh, int *i)
{
	if (tcsh->priority[*i] == ONE_RIGHT
	|| tcsh->priority[*i] == TWO_RIGHT
	|| tcsh->priority[*i] == ONE_LEFT
	|| tcsh->priority[*i] == TWO_LEFT)
		return (1);
	return (0);
}

int operator_tow_left(shell_t *tcsh, int i, char *path)
{
	char *buffer = "\0";
	size_t size = 0;
	int fd = 0;

	if (tcsh->priority[i + 1] == ONE_LEFT) {
		fd = open(path, O_RDONLY);
		if (fd != -1)
			dup2(fd, 0);
	}
	if (tcsh->priority[i + 1] == TWO_LEFT) {
		while (my_strcmp(buffer, path) != 0) {
			my_putstr("? ");
			if (getline(&buffer, &size, stdin) == -1)
				break;
			buffer[my_strlen(buffer) - 1] = '\0';
		}
	}
	return (0);
}

int operator_pipe_redirect_file(shell_t *tcsh, int i, int *pipe, char *path)
{
	int fd = 0;

	if (tcsh->priority[i + 1] == PIPE)
		dup2(pipe[1], 1);
	else if (tcsh->priority[i + 1] == ONE_RIGHT) {
		fd = open(path, O_WRONLY | O_CREAT, 0666);
		if (fd != -1)
			dup2(fd, 1);
	}
	else if (tcsh->priority[i + 1] == TWO_RIGHT) {
		fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd != -1)
			dup2(fd, 1);
	}
	operator_tow_left(tcsh,i, path);
	return (0);
}

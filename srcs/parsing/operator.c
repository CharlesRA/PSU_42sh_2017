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

char *check_redirection(shell_t *new, int *i)
{
	char *str = NULL;

	if (new->priority[*i + 1] == ONE_RIGHT
	|| new->priority[*i + 1] == TWO_RIGHT
	|| new->priority[*i + 1] == ONE_LEFT
	|| new->priority[*i + 1] == TWO_LEFT)
		if (*new->different_command[1] != NULL)
			str = *new->different_command[1];
	// if (str != NULL && (new->priority[*i + 1] == ONE_RIGHT
	// || new->priority[*i + 1] == TWO_RIGHT)
	return (str);
}

int skip_redirection(shell_t *new, int *i)
{
	if (new->priority[*i] == ONE_RIGHT
	|| new->priority[*i] == TWO_RIGHT
	|| new->priority[*i] == ONE_LEFT
	|| new->priority[*i] == TWO_LEFT) {
		return (1);
	}
	return (0);
}

int operator_tow_left(shell_t *new, int i, char *path)
{
	char *buffer = "\0";
	size_t size = 0;
	int fd = 0;

	if (new->priority[i + 1] == ONE_LEFT) {
		fd = open(path, O_RDONLY);
		if (fd != -1)
			dup2(fd, 0);
	}
	if (new->priority[i + 1] == TWO_LEFT) {
		while (my_strcmp(buffer, path) != 0) {
			my_putstr("? ");
			if (getline(&buffer, &size, stdin) == -1)
				break;
			buffer[my_strlen(buffer) - 1] = '\0';
		}
	}
	return (0);
}

int operator_pipe_redirect_file(shell_t *new, int i, int *pipe, char *path)
{
	int fd = 0;

	if (new->priority[i + 1] == PIPE)
		dup2(pipe[1], 1);
	else if (new->priority[i + 1] == ONE_RIGHT) {
		fd = open(path, O_WRONLY | O_CREAT, 0666);
		if (fd != -1)
			dup2(fd, 1);
	}
	else if (new->priority[i + 1] == TWO_RIGHT) {
		fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd != -1)
			dup2(fd, 1);
	}
	operator_tow_left(new, i, path);
	return (0);
}

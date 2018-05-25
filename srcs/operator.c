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

char *check_redirecion(shell_t *new, int *i)
{
	char *str = NULL;

	if (new->priority[*i + 1] == ONE_RIGHT
	|| new->priority[*i + 1] == TWO_RIGHT
	|| new->priority[*i + 1] == ONE_LEFT
	|| new->priority[*i + 1] == TWO_LEFT)
		str = *new->different_command[1];
	return (str);
}

int skip_redirecion(shell_t *new, int *i)
{
	if (new->priority[*i] == ONE_RIGHT
	|| new->priority[*i] == TWO_RIGHT
	|| new->priority[*i] == ONE_LEFT
	|| new->priority[*i] == TWO_LEFT) {
		return (1);
	}
	return (0);
}

static void operator_left(shell_t *new, int i, char *path)
{
	char *buffer = "\0";
	size_t size = 0;

	switch (new->priority[i + 1]) {
	case ONE_LEFT:
		fd = open(path, O_RDONLY);
		dup2(fd, 0);
		break;
	case TWO_LEFT:
		while (my_strcmp(buffer, path) != 0) {
			my_putstr("? ");
			if (getline(&buffer, &size, stdin) == -1)
				break;
			buffer[my_strlen(buffer) - 1] = '\0';
		}
		break;
	default:
		break;
	}
}

int operator_pipe_redirect_file(shell_t *new, int i, int *pipe, char *path)
{
	int mode = O_WRONLY | O_CREAT;
	int fd = 0;

	switch (new->priority[i + 1]) {
	case PIPE:
		dup2(pipe[1], 1);
		break;
	case TWO_RIGHT:
		mode |= O_APPEND;
	case ONE_RIGHT:
		fd = open(path, mode, 0666);
		dup2(fd, 1);
		break;
	default:
		operator_left(new, i, path);
		break;
	}
	return (0);
}

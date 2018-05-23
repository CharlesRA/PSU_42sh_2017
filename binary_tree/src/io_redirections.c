/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** handles input or output redirections
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "minishell.h"

void change_input_output(command_t const *command)
{
	if (command->input != 0)
		dup2(command->input, 0);
	if (command->output != 1) {
		dup2(command->output, 1);
		close(command->output);
	}
}

void close_input_output(command_t const *command)
{
	if (command->input != 0)
		close(command->input);
	if (command->output != 1)
		close(command->output);
}

int get_output(node_t const *node, type_t type)
{
	int mode = O_WRONLY | O_CREAT | (type == TWO_RIGHT_BRACKET ?
					O_APPEND : 0);
	int fd = open(node->data[0], mode, 0666);

	if (fd == -1)
		my_perror(node->data[0]);
	return (fd);
}

int get_input(node_t const *node, type_t type)
{
	char *buffer = NULL;
	size_t size = 0;
	int fd;

	if (type == ONE_LEFT_BRACKET) {
		fd = open(node->data[0], O_RDONLY);
		if (fd == -1)
			my_perror(node->data[0]);
		return (fd);
	}
	do {
		if (buffer)
			free(buffer);
		my_putstr("? ");
		if (getline(&buffer, &size, stdin) == -1)
			break;
		buffer[my_strlen(buffer) - 1] = 0;
	} while (my_strcmp(buffer, node->data[0]) != 0);
	return (1);
}

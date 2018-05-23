/*
** EPITECH PROJECT, 2018
** minishell2
** File description:
** auxiliary to rpn
*/

#include "minishell.h"

void destroy_node(node_t *node)
{
	if (node) {
		if (node->data)
			free(node->data);
		free(node);
	}
}

int is_left_associativity(node_t *data)
{
	(void) data;
	return (1);
}

int precedence(node_t *data)
{
	if (data->type == PIPE ||
	data->type == ONE_LEFT_BRACKET || data->type == TWO_LEFT_BRACKET ||
	data->type == ONE_RIGHT_BRACKET || data->type == TWO_RIGHT_BRACKET)
		return (1);
	if (data->type == SEMICOLON)
		return (0);
	return (-1);
}

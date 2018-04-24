/*
** EPITECH PROJECT, 2018
** minishell2
** File description:
** transforms chained list with rpn
*/

#include "minishell.h"

static int add_to_output(node_t **output, node_t **token)
{
	node_t *tmp;

	if (*output) {
		tmp = *output;
		while (tmp->right)
			tmp = tmp->right;
		tmp->right = *token;
	} else
		*output = *token;
	(*token)->right = NULL;
	(*token)->left = NULL;
	return (0);
}

static int pop_operators(node_t **output, node_t **stack, node_t *token)
{
	node_t *tmp = NULL;

	while (*stack && (precedence(*stack) > precedence(token) ||
		(precedence(*stack) == precedence(token) &&
		is_left_associativity(*stack))) &&
	(*stack)->type != OPEN_PARENTHESIS) {
		tmp = (*stack)->right;
		add_to_output(output, stack);
		*stack = tmp;
	}
	return (0);
}

static int pop_operators_until_open_parenthesis(node_t **output, node_t **stack,
					node_t *token)
{
	node_t *tmp;

	while (*stack && (*stack)->type != OPEN_PARENTHESIS) {
		tmp = (*stack)->right;
		add_to_output(output, stack);
		*stack = tmp;
	}
	if (*stack == NULL)
		return (1);
	tmp = (*stack)->right;
	destroy_node(*stack);
	destroy_node(token);
	*stack = tmp;
	return (0);
}

int list_to_rpn(node_t **root)
{
	node_t *token = (*root)->right;
	node_t *tmp = NULL;
	node_t *stack = NULL;
	node_t *output = NULL;

	while (token) {
		tmp = token->right;
		if (token->type == COMMAND)
			add_to_output(&output, &token);
		else if (token->type == OPEN_PARENTHESIS) {
			token->right = stack;
			stack = token;
		}
		else if (token->type == CLOSED_PARENTHESIS)
			pop_operators_until_open_parenthesis(&output, &stack,
							token);
		else if (token->type != COMMAND) {
			pop_operators(&output, &stack, token);
			token->right = stack;
			stack = token;
		}
		token = tmp;
	}
	while (stack) {
		tmp = stack->right;
		add_to_output(&output, &stack);
		stack = tmp;
	}
	(*root)->right = output;
	return (0);
}

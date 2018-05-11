/*
** EPITECH PROJECT, 2018
** minishell2
** File description:
** creates tree from rpn list
*/

#include "minishell.h"

static int add_to_stack(list_t **stack, node_t *node)
{
	list_t *new = malloc(sizeof(*tcsh));

	if (new == NULL)
		return (1);
	tcsh->node = node;
	tcsh->next = *stack;
	*stack = new;
	return (0);
}

static int pop_sons_from_stack(list_t **stack, node_t *ope)
{
	list_t *tmp = *stack;

	if (tmp == NULL)
		return (1);
	ope->right = (*stack)->node;
	*stack = (*stack)->next;
	free(tmp);
	tmp = *stack;
	if (tmp == NULL)
		return (1);
	ope->left = (*stack)->node;
	*stack = (*stack)->next;
	free(tmp);
	return (0);
}

int make_tree(node_t **root)
{
	node_t *node = (*root)->right;
	node_t *tmp;
	list_t *stack = NULL;

	while (node) {
		while (node && node->type == COMMAND) {
			tmp = node->right;
			node->right = NULL;
			add_to_stack(&stack, node);
			node = tmp;
		}
		if (node) {
			tmp = node->right;
			pop_sons_from_stack(&stack, node);
			add_to_stack(&stack, node);
			node = tmp;
		}
	}
	if (stack == NULL)
		return (1);
	(*root)->right = stack->node;
	free(stack);
	return (0);
}

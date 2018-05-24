/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** handles binary tre
*/

#include "minishell.h"
#include "lexer.h"
#include "str.h"
void destroy_nodes(node_t *node)
{
	if (node == NULL)
		return;
	if (node->left)
		destroy_nodes(node->left);
	if (node->right)
		destroy_nodes(node->right);
	destroy_tab(node->data);
	free(node);
}

static int init_tree(node_t **root)
{
	*root = malloc(sizeof(node_t));
	if (*root == NULL)
		return (1);
	(*root)->data = NULL;
	(*root)->type = ROOT;
	(*root)->parent = NULL;
	(*root)->left = NULL;
	(*root)->right = NULL;
	return (0);
}

static int is_error(node_t **root)
{
	node_t *check = (*root)->right;

	if (check->type == PIPE ||
	check->type == ONE_LEFT_BRACKET || check->type == TWO_LEFT_BRACKET ||
	check->type == ONE_RIGHT_BRACKET || check->type == TWO_RIGHT_BRACKET) {
		my_putstr(NULL_COMMAND);
		(*root)->type = 0;
		return (1);
	}
	for (node_t *node = (*root)->right ; node->right ; node = node->right) {
		check = node->right;
		if ((node->type == PIPE && check->type == TWO_LEFT_BRACKET) ||
		(node->type == ONE_LEFT_BRACKET && check->type == TWO_LEFT_BRACKET) ||
		(node->type == PIPE && check->type == ONE_LEFT_BRACKET) ||
		(node->type == ONE_RIGHT_BRACKET && check->type == TWO_RIGHT_BRACKET) ||
		(node->type == TWO_RIGHT_BRACKET && check->type == TWO_RIGHT_BRACKET) ||
		(node->type == TWO_RIGHT_BRACKET && check->type == ONE_RIGHT_BRACKET) ||
		(node->type == ONE_RIGHT_BRACKET && check->type == ONE_RIGHT_BRACKET) ||
		(node->type == ONE_LEFT_BRACKET && check->type == ONE_LEFT_BRACKET)) {
			my_putstr(AMBIGUOUS);
			(*root)->type = 0;
			return (1);
		}
	}
	return (0);
}

int create_tree(node_t **root, char *cmd)
{
	if (cmd == NULL || init_tree(root) == 1 || lexing(root, cmd) == 1)
		return (1);
	if (is_error(root))
		return (2);
	if (list_to_rpn(root) == 1 || make_tree(root) == 1)
		return (1);
	return (0);
}

/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** handles binary tre
*/

#include "minishell.h"
#include "lexer.h"

void destroy_nodes(node_t *node)
{
	if (node == NULL)
		return;
	if (node->left)
		destroy_nodes(node->left);
	if (node->right)
		destroy_nodes(node->right);
	if (node->data)
		free(node->data);
	free(node);
}

static int init_tree(node_t **root)
{
	*root = malloc(sizeof(node_t));
	if (*root == NULL)
		return (1);
	(*root)->data = NULL;
	(*root)->type = ROOT;
	(*root)->left = NULL;
	(*root)->right = NULL;
	return (0);
}

int create_tree(node_t **root, char *cmd)
{
	if (cmd == NULL || init_tree(root) == 1)
		return (1);
	if (lexing(root, cmd) == 1)
		return (1);
	if (list_to_rpn(root) == 1)
		return (1);
	if (make_tree(root) == 1)
		return (1);
	return (0);
}

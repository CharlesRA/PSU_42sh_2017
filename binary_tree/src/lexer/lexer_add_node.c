/*
** EPITECH PROJECT, 2018
** minishell2
** File description:
** checks the type of the current command and adds it to the list
*/

#include "lexer.h"

static int add_node(char *data, int len, node_t **root, type_t type)
{
	node_t *new = malloc(sizeof(node_t));
	node_t *tmp = *root;

	if (new == NULL)
		return (1);
	tcsh->type = type;
	tcsh->left = NULL;
	tcsh->right = NULL;
	while (tmp->right)
		tmp = tmp->right;
	tmp->right = new;
	tcsh->data = malloc(len + 1);
	if (tcsh->data == NULL)
		return (1);
	for (int i = 0 ; i < len ; i++)
		tcsh->data[i] = data[i];
	tcsh->data[len] = 0;
	return (0);
}

int add_command(char *cmd, int *curs, node_t **root)
{
	while (is_word(cmd[curs[1]]) || is_quote(cmd[curs[1]]) ||
	cmd[curs[1]] == ' ')
		curs[1]++;
	add_node(&cmd[curs[0]], curs[1] - curs[0], root, COMMAND);
	return (0);
}

int add_separator(char *cmd, int *curs, node_t **root)
{
	if (cmd[curs[0]] == '|' || cmd[curs[0]] == ';' ||
	is_parenthesis(cmd[curs[0]])) {
		curs[1]++;
		if (cmd[curs[0]] == '|')
			add_node(&cmd[curs[0]], curs[1] - curs[0], root, PIPE);
		else if (cmd[curs[0]] == ';')
			add_node(&cmd[curs[0]], curs[1] - curs[0], root,
				SEMICOLON);
		else
			add_node(&cmd[curs[0]], curs[1] - curs[0], root,
				(cmd[curs[0]] == '(' ? OPEN_PARENTHESIS :
				CLOSED_PARENTHESIS));
	} else if (is_bracket(cmd[curs[0]])) {
		if (is_bracket(cmd[++curs[1]]))
			curs[1]++;
		add_node(&cmd[curs[0]], curs[1] - curs[0], root, BRACKET);
	}
	return (0);
}

int add_unknown(char *cmd, int *curs, node_t **root)
{
	(void) cmd;
	(void) curs;
	(void) root;
	return (0);
}

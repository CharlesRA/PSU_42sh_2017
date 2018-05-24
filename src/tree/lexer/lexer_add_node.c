/*
** EPITECH PROJECT, 2018
** minishell2
** File description:
** checks the type of the current command and adds it to the list
*/

#include "lexer.h"
#include "str.h"
static int add_node(char *data, int len, node_t *last, type_t type)
{
	node_t *new = malloc(sizeof(node_t));
	char *tmp = NULL;

	if (new == NULL)
		return (1);
	new->type = type;
	new->left = NULL;
	new->right = NULL;
	new->data = NULL;
	last->right = new;
	if (type == COMMAND) {
		tmp = malloc(len + 1);
		if (tmp == NULL)
			return (1);
		for (int i = 0 ; i < len ; i++)
			tmp[i] = data[i];
		tmp[len] = 0;
		new->data = my_str_to_word_array(tmp, ' ');
		free(tmp);
	}
	return (0);
}

int add_command(char *cmd, int *curs, node_t *last)
{
	while (is_word(cmd[curs[1]]) || is_quote(cmd[curs[1]]) ||
	cmd[curs[1]] == ' ')
		curs[1]++;
	return (add_node(&cmd[curs[0]], curs[1] - curs[0], last, COMMAND));
}

int add_separator(char *cmd, int *curs, node_t *last)
{
	type_t type;

	switch (cmd[curs[0]]) {
	case '|':
		type = (cmd[curs[1]] == '|' ? OR : PIPE);
		curs[1] += (type == OR ? 1 : 0);
		break;
	case '&':
		type = (cmd[curs[1]] == '&' ? AND : UNKNOWN);
		curs[1] += (type == AND ? 1 : 0);
		break;
	case ';':
		while (cmd[curs[1]] == ';' || cmd[curs[1]] == ' ' || cmd[curs[1]] == '\t')
			curs[1]++;
		type = SEMICOLON;
		break;
	case '(':
	case ')':
		type = (cmd[curs[0]] == '(' ? OPEN_PARENTHESIS : CLOSED_PARENTHESIS);
		break;
	case '<':
		type = (cmd[curs[1]] == '<' ? TWO_LEFT_BRACKET : ONE_LEFT_BRACKET);
		curs[1] += (type == TWO_LEFT_BRACKET ? 1 : 0);
		break;
	case '>':
		type = (cmd[curs[1]] == '>' ? TWO_RIGHT_BRACKET : ONE_RIGHT_BRACKET);
		curs[1] += (type == TWO_RIGHT_BRACKET ? 1 : 0);
		break;
	default:
		return (1);
	}
	return (add_node(&cmd[curs[0]], curs[1] - curs[0], last, type));
}

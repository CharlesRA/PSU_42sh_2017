/*
** EPITECH PROJECT, 2018
** minishell2
** File description:
** checks the type of the current command and adds it to the list
*/

#include "lexer.h"
#include "str.h"

static int add_node(char **data, int length, node_t *last, type_t type)
{
	node_t *new = malloc(sizeof(node_t));

	if (new == NULL)
		return (1);
	new->type = type;
	new->left = NULL;
	new->right = NULL;
	new->data = NULL;
	last->right = new;
	if (type == COMMAND) {
		new->data = malloc(sizeof(char *) * (length + 1));
		if (new->data == NULL)
			return (1);
		for (int i = 0 ; i < length ; i++) {
			new->data[i] = my_strdup(data[i]);
			if (new->data[i] == NULL)
				return (1);
		}
		new->data[length] = NULL;
	}
	return (0);
}

int add_command(char **cmd, node_t *last, int *i)
{
	int tmp = 1;

	while (cmd[tmp] && (is_word(cmd[tmp][0]) || is_quote(cmd[tmp][0])))
		tmp++;
	*i += tmp - 1;
	return (add_node(&cmd[0], tmp, last, COMMAND));
}

int add_separator(char *cmd, node_t *last)
{
	type_t type;

	switch (cmd[0]) {
	case '|':
		type = (cmd[1] == '|' ? OR : PIPE);
		break;
	case '&':
		type = (cmd[1] == '&' ? AND : UNKNOWN);
		break;
	case ';':
		type = SEMICOLON;
		break;
	case '(':
	case ')':
		type = (cmd[1] == '(' ? OPEN_PARENTHESIS : CLOSED_PARENTHESIS);
		break;
	case '<':
		type = (cmd[1] == '<' ? TWO_LEFT_BRACKET : ONE_LEFT_BRACKET);
		break;
	case '>':
		type = (cmd[1] == '>' ? TWO_RIGHT_BRACKET : ONE_RIGHT_BRACKET);
		break;
	default:
		return (1);
	}
	return (add_node(&cmd, 0, last, type));
}

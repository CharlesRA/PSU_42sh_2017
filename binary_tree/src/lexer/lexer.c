/*
** EPITECH PROJECT, 2018
** minishell2
** File description:
** lexer
*/

#include "lexer.h"

static int is_command(char c)
{
	if (is_word(c) || is_quote(c))
		return (1);
	return (0);
}

static int is_separator(char c)
{
	if (c == '|' || c == ';' || is_bracket(c) || is_parenthesis(c))
		return (1);
	return (0);
}

int lexing(node_t **root, char *cmd)
{
	int curs[2] = {0, 0};

	while (cmd[curs[0]]) {
		if (is_command(cmd[curs[0]]))
			add_command(cmd, curs, root);
		else if (is_separator(cmd[curs[0]]))
			add_separator(cmd, curs, root);
		else
			add_unknown(cmd, curs, root);
		while (cmd[curs[1]] == ' ' || cmd[curs[1]] == '\t')
			curs[1]++;
		curs[0] = curs[1];
	}
	return (0);
}

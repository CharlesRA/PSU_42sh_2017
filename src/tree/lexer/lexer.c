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
	if (c == '&' || c == '|' || c == ';' || is_bracket(c) || is_parenthesis(c))
		return (1);
	return (0);
}

int lexing(node_t **root, char *cmd)
{
	node_t *last = *root;
	char **array = my_str_to_word_array(cmd, ' ');
	int ret = 0;

	if (array == NULL)
		return (1);
	for (int i = 0 ; array[i] && ret == 0 ; i++) {
		if (is_command(array[i][0]))
			ret = add_command(&array[i], last, &i);
		else if (is_separator(array[i][0]))
			ret = add_separator(array[i], last);
		last = last->right;
	}
	return (ret);
}

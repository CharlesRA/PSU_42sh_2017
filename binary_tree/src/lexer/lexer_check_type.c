/*
** EPITECH PROJECT, 2018
** minishell2
** File description:
** aux
*/

int is_quote(char c)
{
	return (c == '\"' || c == '\'');
}

int is_word(char c)
{
	return ((c >= '*' && c <= ':') || (c >= '?' && c<= '{') ||
		c == '=' || c == '}' || c == '~' || c == '!' ||
		(c >= '#' && c <= '%'));
}

int is_bracket(char c)
{
	return (c == '<' || c == '>');
}

int is_parenthesis(char c)
{
	return (c == '(' || c == ')');
}

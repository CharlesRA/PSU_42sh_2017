/*
** EPITECH PROJECT, 2018
** minishell2
** File description:
** aux
*/

int is_quote(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	return (0);
}

int is_word(char c)
{
	return ((c >= '*' && c <= ':') || (c >= '?' && c <= '{') ||
		c == '=' || c == '}' || c == '~' || c == '!' ||
		(c >= '#' && c <= '%'));
}

int is_bracket(char c)
{
	if (c == '<')
		return (1);
	else if (c == '>')
		return (2);
	return (0);
}

int is_parenthesis(char c)
{
	if (c == '(')
		return (1);
	else if (c == ')')
		return (2);
	return (0);
}

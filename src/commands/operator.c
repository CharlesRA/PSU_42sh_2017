/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** operator.c
*/

int operator(char c)
{
	if (c == ';'
	|| c == '|'
	|| c == '<'
	|| c == '>')
		return (1);
	return (0);
}

int char_is_an_operator(char const *str, int *i, int mod)
{
	if ((str[*i] == ';'
	|| str[*i] == '|'
	|| (str[*i] == '<' && str[*i + 1] == '<')
	|| ((str[*i] == '>' && str[*i + 1] == '>') && mod == 1))) {
		if ((str[*i] == '<' && str[*i + 1] != '<')
		|| (str[*i] == '>' && str[*i + 1] != '>'))
			i += 1;
		return (1);
	}
	return (0);
}

/*
** EPITECH PROJECT, 2017
** my_str_isnum
** File description:
** returns 1 if the string is only digits
*/

int my_str_isnum(char const *str)
{
	for (int i = 0 ; str[i] ; i++)
		if (str[i] > '9' || str[i] < '0')
			return (0);
	return (1);
}

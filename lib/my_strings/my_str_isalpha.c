/*
** EPITECH PROJECT, 2017
** my_str_isalpha
** File description:
** returns 1 if the string is only alphabetical chars
*/

int my_str_isalpha(char const *str)
{
	for (int i = 0 ; str[i] ; i++)
		if ((str[i] < 'A' || str[i] > 'Z') &&
		(str[i] < 'a' || str[i] > 'z'))
			return (0);
	return (1);
}

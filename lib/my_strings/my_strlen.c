/*
** EPITECH PROJECT, 2017
** my_strlen
** File description:
** returns the number of chars in a char string
*/

int my_strlen(char const *str)
{
	int i = 0;

	if (str)
		while (str[i])
			i++;
	return (i);
}

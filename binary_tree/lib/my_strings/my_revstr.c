/*
** EPITECH PROJECT, 2017
** my_revstr
** File description:
** reverse a char string
*/

int my_strlen(char const *str);

char *my_revstr(char *str)
{
	int i = my_strlen(str);
	int n = 0;
	char tmp;

	for (--i ; n < i ; n++) {
		tmp = str[n];
		str[n] = str[i];
		str[i--] = tmp;
	}
	return (str);
}

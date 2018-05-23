/*
** EPITECH PROJECT, 2017
** my_strncat
** File description:
** concatenates n bytes at the end of the dest string
*/

int my_strlen(char const *str);

char *my_strncat(char *dest, char const *src, int nb)
{
	int len = my_strlen(dest);

	for (int i = 0 ; src[i] && i < nb ; i++)
		dest[len++] = src[i];
	dest[len] = 0;
	return (dest);
}

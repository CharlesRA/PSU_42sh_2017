/*
** EPITECH PROJECT, 2017
** my_strcat
** File description:
** concatenates two strings
*/

int my_strlen(char const *str);

char *my_strcat(char *dest, char const *src)
{
	int len = my_strlen(dest);

	for (int i = 0 ; src[i] ; i++) {
		dest[len] = src[i];
		len++;
	}
	dest[len] = 0;
	return (dest);
}

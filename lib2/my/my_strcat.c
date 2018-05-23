/*
** EPITECH PROJECT, 2017
** my_strcat
** File description:
** task02
*/

#include "str.h"

char	*my_strcat(char *dest, char *src)
{
	int len;
	char a;

	len = my_strlen(dest);
	int	i = 0;
	while (src[i] != '\0') {
		a = src[i];
		dest[len + i] = a;
		i++;
	}
	dest[len + i] = src[i];
	return (dest);
}

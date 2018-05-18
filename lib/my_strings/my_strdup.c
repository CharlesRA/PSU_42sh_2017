/*
** EPITECH PROJECT, 2017
** my_strdup
** File description:
** dynamically allocates memory and copies given string
*/

#include <stdlib.h>

int my_strlen(char const *src);

char *my_strdup(char const *src)
{
	int i;
	int len = my_strlen(src);
	char *dest = malloc(len + 1);

	for (i = 0 ; i < len ; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

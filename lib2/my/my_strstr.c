/*
** EPITECH PROJECT, 2017
** strstr
** File description:
** string.h
*/

#include "str.h"

int my_strstr(char *str, char const *to_find)
{
	int i = 0;

	while (str[i] != '\0' || to_find[i] != '\0') {
		if (str[i] != to_find[i])
			return (0);
		i++;
		if (str[i] == '\0' || to_find[i] == '\0')
			return (1);
	}
	return (0);
}

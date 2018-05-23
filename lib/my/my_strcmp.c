/*
** EPITECH PROJECT, 2017
** my_strcmp.c
** File description:
** look if 2 files are equal
*/

#include <stdlib.h>

int my_strcmp(char const *s1, char const *s2)
{
	int i = 0;
	int diff = 0;

	if (s1 == NULL || s2 == NULL)
		return (84);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i += 1;
	diff = s1[i] - s2[i];
	return (diff);
}

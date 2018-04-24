/*
** EPITECH PROJECT, 2018
** tabs
** File description:
** handle tabs
*/

#include <stdlib.h>
#include "my_strings.h"

int my_tablen(char **tab)
{
	int i = 0;

	if (tab)
		while (tab[i])
			i++;
	return (i);
}

char **my_tabdup(char **tab)
{
	int len = my_tablen(tab);
	char **dup = malloc(sizeof(char *) * (len + 1));

	if (dup == NULL)
		return (NULL);
	for (int i = 0 ; i < len ; i++)
		dup[i] = my_strdup(tab[i]);
	dup[len] = NULL;
	return (dup);
}

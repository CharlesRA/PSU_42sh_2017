/*
** EPITECH PROJECT, 2018
** triple tabs
** File description:
** handle triple tabs
*/

#include <stdlib.h>
#include "my_strings.h"

int my_triple_tablen(char ***tab)
{
	int i = 0;

	if (tab)
		while (tab[i])
			i++;
	return (i);
}

char ***my_triple_tabdup(char ***tab)
{
	int len = my_triple_tablen(tab);
	char ***dup = malloc(sizeof(char **) * (len + 1));

	if (dup == NULL)
		return (NULL);
	for (int i = 0 ; i < len ; i++)
		dup[i] = my_tabdup(tab[i]);
	dup[len] = NULL;
	return (dup);
}

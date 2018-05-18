/*
** EPITECH PROJECT, 2018
** destroy
** File description:
** destroys tabs
*/

#include <stdlib.h>

void destroy_tab(char **tab)
{
	if (tab) {
		for (int i = 0 ; tab[i] ; i++)
			free(tab[i]);
		free(tab);
		tab = NULL;
	}
}

void destroy_triple_tab(char ***tab)
{
	if (tab) {
		for (int i = 0 ; tab[i] ; i++)
			destroy_tab(tab[i]);
		free(tab);
		tab = NULL;
	}
}

/*
** EPITECH PROJECT, 2017
** mem_alloc_2d_array
** File description:
** allocates and returns a pointer to a 2D array
*/

#include <stdlib.h>

char **mem_alloc_2d_array(int nb_rows, int nb_cols)
{
	char **tab = malloc(sizeof(char *) * nb_rows);

	if (!tab)
		return (0);
	for (int i = 0 ; i < nb_rows ; i++) {
		tab[i] = malloc(nb_cols);
		if(!tab[i])
			return (0);
	}
	return (tab);
}

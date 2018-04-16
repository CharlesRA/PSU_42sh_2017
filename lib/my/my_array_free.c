/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** my_array_free.c
*/

#include <stdlib.h>

void my_array_free(char **ptr)
{
	for (int i = 0; ptr[i] != NULL; i++)
		free(ptr[i]);
	free(ptr);
}

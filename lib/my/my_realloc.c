/*
** EPITECH PROJECT, 2018
** realloc
** File description:
** lib
*/

#include "str.h"

void my_realloc_char(void *ptr, int size)
{
	ptr = malloc(sizeof(typeof(char)) * size);
	if (ptr == NULL)
		exit(84);
}

void my_realloc_char_star(void *ptr, int size)
{
	ptr = malloc(sizeof(char *) * size);
	if (ptr == NULL)
		exit(84);
}

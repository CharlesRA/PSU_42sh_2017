/*
** EPITECH PROJECT, 2017
** mem_alloc
** File description:
** allocates and copy two strings and returns a pointer to the memory address
*/

#include <stdlib.h>

static int my_strlen(char const *str)
{
	int i = 0;

	if (str) {
		while (str[i])
			i++;
	}
	return (i);
}
char *mem_alloc(char const *a, char const *b)
{
	int la = my_strlen(a);
	int lb = my_strlen(b);
	char *c = malloc(la + lb + 1);
	int i = 0;

	if (c == NULL)
		return (NULL);
	while (i < la) {
		c[i] = a[i];
		i++;
	}
	for (int j = 0 ; j < lb ; j++)
		c[i++] = b[j];
	c[i] = 0;
	return (c);
}

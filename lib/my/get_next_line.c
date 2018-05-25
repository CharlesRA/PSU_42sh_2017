/*
** EPITECH PROJECT, 2018
** get_next_line
** File description:
** CPE
*/

#include <unistd.h>
#include <stdlib.h>
#include "str.h"

int check_backslash_n(char const *str)
{
	int i = 0;

	while (str[i] != '\0') {
		if (str[i] == '\n')
			return (++i);
		i++;
	}
	return (0);
}

char *recons(char *buffer, char *result, int to_copy)
{
	int len = my_strlen(result);
	int i = 0;

	buffer = malloc(sizeof(char) * len + 1);
	while (i != to_copy) {
		buffer[i] = result[i];
		i++;
	}
	buffer[i - 1] = '\0';
	i = 0;
	while (result[to_copy] != '\0') {
		result[i] = result[to_copy];
		i++;
		to_copy++;
	}
	result[i] = '\0';
	return (buffer);
}

char *get_next_line(int fd)
{
	static char *result = NULL;
	char *buffer = malloc(2);
	int nbr = 0;
	int to_copy = 0;

	if (buffer == NULL)
		return (NULL);
	nbr = read(fd, buffer, 1);
	if (nbr < 1) {
		free(buffer);
		return (NULL);
	}
	buffer[nbr] = '\0';
	result = my_strdupcat(result, buffer);
	to_copy = check_backslash_n(result);
	if (to_copy != 0) {
		buffer = recons(buffer, result, to_copy);
		return (buffer);
	}
	get_next_line(fd);
}

/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** get_next_line.c
*/

#include "linked_list.h"
#include <stdlib.h>
#include "shell.h"
#include "str.h"
#include <string.h>
#include <stdio.h>

int check_backslash_n(char *str)
{
	int i = 0;
	int mod = 0;

	while (str[i] != '\0') {
		if (str[i] == '\n') {
			mod = 1;
			i++;
			break;
		}
		i++;
	}
	if (mod == 0)
		return (0);
	return (i);
}

char* recons(char *buffer, char *result, int to_copy)
{
	int len = 0;
	int i = 0;

	len = my_strlen(result);
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

char *get_next_line(int fd, circular_dll_t *list)
{
	char *buffer = calloc(3, sizeof(char) * 3 + 1);
	static char *result = NULL;
	int nbr = 0;
	int to_copy = 0;

	if (buffer == NULL)
		return (NULL);
	nbr = read(fd, buffer, 3);
	buffer[(nbr == -1 ? 0 : nbr)] = '\0';
	if (nbr < 1 || buffer[0] == 4)
		return (NULL);
	if (nbr != 3) {
		print_and_complete(&buffer, &result, list);
		delete_key(buffer, result);
		result = my_strdupcat(result, buffer);
		to_copy = check_backslash_n(result);
		if (to_copy != 0) {
			buffer = recons(buffer, result, to_copy);
			return (buffer);
		}
	}
	get_next_line(fd, list);
}

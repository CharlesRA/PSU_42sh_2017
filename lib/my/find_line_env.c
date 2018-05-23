/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** find_line_env.c
*/

#include "str.h"

int find_correct_line_env(char **env, char *to_find)
{
	int i = 0;

	while (env[i] != NULL) {
		if (my_strstr(env[i], to_find)) {
			return (i);
		}
		i++;
	}
	return (-1);
}

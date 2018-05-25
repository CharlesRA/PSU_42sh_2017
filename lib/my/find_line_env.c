/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** find_line_env.c
*/

#include "str.h"

int find_correct_line_env(char **env, char const *to_find)
{
	for (int i = 0 ; env[i] != NULL ; i++)
		if (my_strstr(env[i], to_find))
			return (i);
	return (-1);
}

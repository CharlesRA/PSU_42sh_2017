/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** echo.c
*/

#include "str.h"
#include "shell.h"

char **print_echo(shell_t *new, char **env)
{
	for (int i = 1; new->different_command[0][i] != NULL; i++) {
		my_putstr(new->different_command[0][i]);
		if (new->different_command[0][i + 1] != NULL)
			my_putstr(" ");

	}
	my_putstr("\n");
	return (env);
}

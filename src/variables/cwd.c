/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** cwd special variable
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "variables.h"

int change_cwd(variable_t *cwd)
{
	cwd->value = getcwd(cwd->value, 0);
	if (cwd->value == NULL) {
		fprintf(stderr, "Error getting current working directory\n");
		return (1);
	}
	return (0);
}

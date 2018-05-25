/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** globbing.c
*/

#include <glob.h>
#include <stdlib.h>
#include "linked_list.h"
#include "str.h"
#include "shell.h"

int is_globing(char *str)
{
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == '['
		|| str[i] == ']'
		|| str[i] == '*'
		|| str[i] == '?') {
			return (1);
		}
	}
	return (0);
}

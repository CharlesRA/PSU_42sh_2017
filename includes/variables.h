/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** variables handling
*/

#ifndef VAR42_
#define VAR42_

#include "linked_list.h"

typedef struct s_variable {
	char *name;
	char *value;
} variable_t;

static const char *const special_variables[] = {"cwd", "term", "precmd",
						"cwdcmd", "ignoreof"};

char *replace_variable(circular_dll_t *, char **, char *);
void add_variable(circular_dll_t *variables, variable_t *new_variable);
variable_t *set_new_variable(variable_t *new_variable, char *value);

#endif /* VAR42_ */

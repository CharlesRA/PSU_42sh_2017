/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** variables handling
*/

#ifndef VAR42_
#define VAR42_

#include "linked_list.h"

typedef struct s_variable variable_t;
struct s_variable
{
	char *name;
	char *value;
};

static const char *const special_variables[] = {"cwd", "term", "precmd",
						"cwdcmd", "ignoreof"};

variable_t *set_new_variable(variable_t *new_variable, char *value);
int replace_variable(circular_dll_t *, char **, char *);
void add_variable(circular_dll_t *variables, variable_t *new_variable);

#endif /* VAR42_ */

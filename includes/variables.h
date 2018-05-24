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

int replace_variable(circular_dll_t *, char **, char *);

#endif /* VAR42_ */

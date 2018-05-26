/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** variables handling
*/

#ifndef VAR42_
#define VAR42_

#include "shell.h"
#include "linked_list.h"

typedef struct s_variable variable_t;
struct s_variable
{
	char *name;
	char *value;
};

int handle_cwd(shell_t *new, char **envp, variable_t *cwd);
int handle_ignoreeof(shell_t *new, char **envp, variable_t *ignoreeof);
int handle_term(shell_t *new, char **envp, variable_t *term);

typedef int (*spe_var)(shell_t *, char **, variable_t *);

typedef struct s_spe_var_func spe_var_func_t;
struct s_spe_var_func
{
	char *name;
	spe_var function;
};

static const spe_var_func_t special_variables[] = {{"cwd", handle_cwd},
						{"ignoreeof", handle_ignoreeof},
						{"term", handle_term},
						{NULL, NULL}};

char *replace_variable(circular_dll_t *, char **, char *);

#endif /* VAR42_ */

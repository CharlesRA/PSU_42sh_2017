/*
** EPITECH PROJECT, 2018
** builtin_function
** File description:
** minishell
*/

#ifndef BUILTINS_H
#define BUILTINS_H

/*_______________________________BUIlTINS_____________________________________*/
char **change_directory(shell_t *tcsh, char **env);
char **unset_env(shell_t *tcsh, char **envp);
char **set_env(shell_t *tcsh, char **envp);
char *find_home(char **env);
int check_builtin(shell_t *tcsh, char *command);
char **print_env(shell_t *tcsh, char **envp);
char **apply_builtin(const char *command, shell_t *tcsh, char **envp);
/*____________________________________________________________________________*/


struct s_flags {
	char *builtin;
	void *function;
};

static struct s_flags tab[] = {
	{"cd", &change_directory},
	{"env", &print_env},
	{"setenv", &set_env },
	{"unsetenv", &unset_env},
	{"alias", NULL},
	{"exit", NULL},
	{"!!", NULL},
	{NULL, NULL},
};

#endif

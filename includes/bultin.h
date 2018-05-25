/*
** EPITECH PROJECT, 2018
** builtin_function
** File description:
** minishell
*/

#ifndef BUILTIN_H
#define BUILTIN_H

char **unset_env(shell_t *new, char **envp);
char **set_env(shell_t *new, char **envp);
char *find_home(char **env);
int check_builtin(shell_t *new, char *command);
char **print_env(shell_t *new, char **envp);
char **apply_builtin(const char *command, shell_t *new, char **envp);
char **print_echo(shell_t *new, char **env);

struct s_flags {
	char *builtin;
	void *function;
};

static struct s_flags tab[] = {
	{"cd", &change_directory},
	{"env", &print_env},
	{"setenv", &set_env },
	{"unsetenv", &unset_env},
	{"echo", &print_echo},
	{"exit", NULL},
	{NULL, NULL},
};

#endif

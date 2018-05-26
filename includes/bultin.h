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
int check_builtin(char *command);
char **print_env(shell_t *new, char **envp);
char **apply_builtin(const char *command, shell_t *new, char **envp);
char **print_echo(shell_t *new, char **env);
char **declare_variable(shell_t *data, char **envp);
char **create_alias(shell_t *new, char **env);
char **exit_shell(shell_t *new, char **env);
char **display_which(shell_t *new, char **env);

struct s_flags {
	char *builtin;
	void *function;
	int to_be_fork;
};

static struct s_flags tab[] = {
	{"cd", &change_directory, 0},
	{"env", &print_env, 1},
	{"setenv", &set_env , 0},
	{"unsetenv", &unset_env, 0},
	{"echo", &print_echo, 1},
	{"set", &declare_variable, 0},
	{"alias", &create_alias, 0},
	{"exit", &exit_shell, 0},
	{"which", &display_which, 1},
	{NULL, NULL, 0},
};

#endif

/*
** EPITECH PROJECT, 2018
** main
** File description:
** minishell
*/

#include "shell.h"

int main(int ac, char **av, char **envp)
{
	shell_t new;
	circular_dll_t *list = create_list();

	new.variables = create_list();
	new.history = create_list();
	new.return_value = 0;
	new.alias = create_list();
	if (list == NULL
	|| new.alias == NULL
	|| new.variables == NULL
	|| new.history == NULL
	|| init_ncurses(envp, list) == EXIT_FAIL)
		return (EXIT_FAIL);
	loop(&new, envp, list);
	if (isatty(0) == 1 && non_canonic_mode(1) == 84)
		return (EXIT_FAIL);
	return (EXIT_NORMAL);
}

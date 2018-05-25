/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** witch.c
*/

#include "shell.h"
#include <stdio.h>

char **display_which(shell_t *tcsh, char **env)
{
	if (my_array_len(tcsh->different_command[0]) == 1) {
		fprintf(stderr, "which: Too few arguments.\n");
		tcsh->return_value = 1;
	}
	for (int i = 1; tcsh->different_command[0][i] != NULL; i++) {
		if (check_builtin(tcsh->different_command[0][i]) == 1) {
			printf("%s: shell built-in command.\n"
			, tcsh->different_command[0][i]);
		}

	}
	fflush(stdout);
}

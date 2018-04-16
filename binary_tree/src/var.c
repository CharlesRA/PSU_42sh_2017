/*
** EPITECH PROJECT, 2018
** var
** File description:
** check for var and replaces it
*/

#include <stdint.h>
#include <stdlib.h>
#include "my_strings.h"

static int replace_var(char **str, char **envp, uint8_t ret)
{
	int len = my_strlen(*str) - 1;

	if (my_strcmp(*str, "$?") == 0) {
		free(*str);
		return (my_itoa(ret, str));
	}
	for (int i = 0 ; envp[i] ; i++)
		if (my_strncmp(envp[i], &str[0][1], len) == 0) {
			free(*str);
			str[0] = my_strdup(&envp[i][len + 1]);
			return (0);
		}
	free(*str);
	return (1);
}

char **check_replace_var(char **tab, char **envp, uint8_t ret)
{
	for (int i = 0 ; tab[i] ; i++) {
		if (tab[i][0] == '$')
			replace_var(&tab[i], envp, ret);
	}
	return (tab);
}

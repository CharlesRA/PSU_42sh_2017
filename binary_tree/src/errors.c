/*
** EPITECH PROJECT, 2018
** minishell2
** File description:
** handle error functions
*/

#include <string.h>
#include <errno.h>
#include "minishell.h"

int is_number(char c)
{
	return (c >= '0' && c <= '9');
}

int is_letter(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int is_alphanum(char const *str)
{
	for (int i = 0 ; str[i] ; i++)
		if (is_letter(str[i]) == 0 && is_number(str[i]) == 0)
			return (0);
	return (1);
}

int my_perror(char const *str)
{
	int i = 0;
	char *err = strerror(errno);
	char *message = malloc(my_strlen(str) + my_strlen(err) + 5);

	if (message == NULL)
		return (1);
	for ( ; str[i] ; i++)
		message[i] = str[i];
	message[i++] = ':';
	message[i++] = ' ';
	for (int j = 0 ; err[j] ; j++)
		message[i++] = err[j];
	message[i++] = '.';
	message[i++] = '\n';
	message[i] = 0;
	my_puterror(message);
	free(message);
	return (0);
}

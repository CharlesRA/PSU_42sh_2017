/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** check_string.c
*/

#include "str.h"

int string_is_operator(char *command)
{
	if (my_strcmp(command, "|") == 0
	|| my_strcmp(command, ";") == 0
	|| my_strcmp(command, "<") == 0
	|| my_strcmp(command, "<<") == 0
	|| my_strcmp(command, ">") == 0
	|| my_strcmp(command, "&&") == 0
	|| my_strcmp(command, "||") == 0
	|| my_strcmp(command, ">>") == 0)
		return (1);
	return (0);
}

char *get_next_word(char **end, char *str, char extra, int *indice)
{
	char *word;
	int len = 0;
	int i = 0;

	for (; str[i] == extra || (str[i] > 0 && str[i] <= 32); i++);
	str += i;
	if (my_strlen(str) == 0) {
		*indice = 1;
		return (str);
	}
	len = calcul_len(str, extra);
	word = malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		return (NULL);
	for (int i = 0 ; i < len ; i++)
		word[i] = str[i];
	word[len] = '\0';
	*end = str + len;
	return (word);
}

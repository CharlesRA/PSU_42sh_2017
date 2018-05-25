/*
** EPITECH PROJECT, 2018
** my_str_to_word_array.c
** File description:
** split a string in array of word
*/

#include "str.h"

int my_char_isalpha_num(char alpha)
{
	if (alpha > 47 && alpha < 58)
		return (1);
	else
		return (0);
}

int my_str_isspace_num(char *str)
{
	int count = 0;

	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == ' ' || (str[i] > 47 && str[i] < 58))
			count++;
	}
	if (count == my_strlen(str) - 1)
		return (1);
	return (0);
}

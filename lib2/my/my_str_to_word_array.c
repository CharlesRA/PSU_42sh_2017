/*
** EPITECH PROJECT, 2018
** libmy
** File description:
** str to word array
*/

#include <stdlib.h>
#include "str.h"

int increase_count(char const *str, int i, int count)
{
	if (operator(str[i]) == 1 && str[i + 1] > 32)
		count += 2;
	if (operator(str[i]) == 1)
		count++;
	return (count);
}

int count_words(char const *str, char extra)
{
	int count = 1;

	for (int i = 0; str[i]; i++) {
		if (str[i] == extra || char_is_an_operator(str, &i, 1) == 1
		|| (str[i] > 0 && str[i] <= 32 &&
		str[i + 1] > 32)) {
			count = increase_count(str, i, count);
			count++;
		}
	}
	return (count);
}

int increase_len(char const *str, int *len)
{

	if (*len > 0 && operator(str[*len]) == 1)
		return (1);
	if (operator(str[*len]) == 1 && operator(str[*len + 1]) == 1) {
		*len = 2;
		return (1);
	}
	if (operator(str[*len]) == 1) {
		if (operator(str[*len + 1]) == 0) {
			*len += 1;
			return (1);
		}
	}
	return (0);
}

int calcul_len(char const *str, char extra)
{
	int len = 0;

	for (; str[len] != extra && str[len] > 32; len++) {
		if (str[len] == '\0')
			break;
		if (increase_len(str, &len) == 1)
			break;
	}
	return (len);
}

char **my_str_to_word_array(char *str, char extra)
{
	if (str == NULL || extra < 0)
		return (NULL);
	char *copy = str;
	int size = count_words(str, extra);
	char **word_array = malloc(sizeof(char *) * (size + 1));
	int indice = 0;
	int i = 0;

	if (word_array == NULL)
		return (NULL);
	for (; i < size; i++){
		word_array[i] = get_next_word(&str, str, extra, &indice);
		if (indice == 1) {
			break;
		}
		if (word_array[i] == NULL)
			return (NULL);
	}
	word_array[i] = NULL;
	str = copy;
	return (word_array);
}

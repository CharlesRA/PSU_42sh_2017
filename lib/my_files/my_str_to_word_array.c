/*
** EPITECH PROJECT, 2017
** my_str_to_word_array
** File description:
** splits a string into words and store them in a tab
*/

#include <stdlib.h>

static int is_in_str(char c, char const *str)
{
	for (int i = 0 ; str[i] ; i++)
		if (c == str[i])
			return (1);
	return (0);
}

static int my_count_words(char const *str, char const *d)
{
	int i = 0;
	int cnt = 0;

	if (str == NULL)
		return (0);
	while (str[i] && is_in_str(str[i], d))
		i++;
	while (str[i]) {
		cnt++;
		while (str[i] && is_in_str(str[i], d) == 0)
			i++;
		while (str[i] && is_in_str(str[i], d))
			i++;
	}
	return (cnt);
}

static int word_len(char const *str, char const *d)
{
	int n = 0;

	while (str[n] && is_in_str(str[n], d) == 0)
		n++;
	return (n);
}

char **my_str_to_word_array(char const *str, char const *d)
{
	char **tab = malloc(sizeof(char *) * (my_count_words(str, d) + 1));
	int cnt = 0;
	int i = 0;

	if (str == NULL || tab == NULL)
		return (NULL);
	while (str[i] && is_in_str(str[i], d))
		i++;
	for (int n = 0 ; str[i] ; n = 0) {
		tab[cnt] = malloc(word_len(&str[i], d) + 1);
		if (tab[cnt] == NULL)
			return (NULL);
		while (str[i] && is_in_str(str[i], d) == 0)
			tab[cnt][n++] = str[i++];
		tab[cnt++][n] = 0;
		while (str[i] && is_in_str(str[i], d))
			i++;
	}
	tab[cnt] = NULL;
	return (tab);
}

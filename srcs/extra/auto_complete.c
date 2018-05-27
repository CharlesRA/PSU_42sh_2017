/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** auto_complete.c
*/

#include <string.h>
#include "shell.h"

static char *clear_text(char *buffer, char *auto_complete, char *result)
{
	int len = strlen(buffer);
	char *string = NULL;

	for (int i = 0; i != len; i++)
		write(1 , "\b \b", strlen("\b \b"));
	result[strlen(result) - len] = '\0';
	string = my_strdupcat(result, auto_complete);
	my_putstr(auto_complete);
	return (string);
}

static circular_dll_t *init_data(circular_dll_t *list)
{
	circular_dll_t *data = list->go_to[NEXT];

	while (data != list) {
		if (strlen(((complete_t *)data->data)->valid) != 0)
			return (data);
		data = data->go_to[NEXT];
	}
	return (data);
}

static char *check_valid_path(circular_dll_t *list, char *result, char *arg)
{
	circular_dll_t *temp = list->go_to[NEXT];
	circular_dll_t *data = init_data(list);
	size_t len = 1;

	if (data == list)
		return (arg);
	for ( ; len != strlen(((complete_t *)data->data)->valid) ; len++) {
		temp = list->go_to[NEXT];
		while (temp != list) {
			if (strlen(((complete_t *)temp->data)->valid) != 0
			&& strncmp(((complete_t *)data->data)->valid
			, ((complete_t *)temp->data)->valid, len) != 0)
				return (clear_text(arg, strndup(((complete_t *)
				data->data)->valid, --len), result));
			temp = temp->go_to[NEXT];
		}
	}
	return (clear_text(arg,
	strndup(((complete_t *)data->data)->valid, len), result));
}

static char *auto_complete(char *result, circular_dll_t *list, char *line)
{
	circular_dll_t *temp = list->go_to[NEXT];
	char **info = NULL;
	char *arg = NULL;

	if (strlen(result) == 0)
		return (result);
	info = my_str_to_word_array(result, ' ');
	arg = info[my_array_len(info) - 1];
	while (temp != list) {
		if (strncmp(arg, ((complete_t *)temp->data)->file
		, strlen(arg)) == 0) {
			((complete_t *)temp->data)->valid =
			strdup(((complete_t *)temp->data)->file);
		}
		else {
			((complete_t *)temp->data)->valid = "\0";
		}
		temp = temp->go_to[NEXT];
	}
	return (check_valid_path(list, result, arg));
}

void print_and_complete(char **buffer
, char **result , circular_dll_t *list)
{
	static int passage = 0;

	if (passage == 0)
		*result = strdup("\0");
	if (*buffer[0] != 9)
		my_putstr(*buffer);
	else {
		*buffer = auto_complete(*result, list, *buffer);
		*result[0] = '\0';
	}
	passage++;
}

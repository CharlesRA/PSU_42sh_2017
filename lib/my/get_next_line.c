/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** get_next_line.c
*/

#include "linked_list.h"
#include <stdlib.h>
#include "shell.h"
#include "str.h"
#include <string.h>
#include <stdio.h>

char *clear_text(char *buffer, char *auto_complete, char *result)
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

char *check_valid_path(circular_dll_t *list, char *result, char *arg)
{
	circular_dll_t *temp = list->go_to[NEXT];
	circular_dll_t *data = list->go_to[NEXT];
	int len = 1;

	while(data != list) {
		if (strlen(((complete_t *)data->data)->valid) != 0)
			break;
		data = data->go_to[NEXT];
	}
	if (data == list) {
		return (arg);
	}
	while (len != strlen(((complete_t *)data->data)->valid)) {
		temp = list->go_to[NEXT];
		while (temp != list) {
			if (strlen(((complete_t *)temp->data)->valid) != 0
			&& strncmp(((complete_t *)data->data)->valid, ((complete_t *)temp->data)->valid, len) != 0) {
				len--;
				return (clear_text(arg, strndup(((complete_t *)data->data)->valid, len), result));
			}
			temp = temp->go_to[NEXT];
		}
		len++;
	}
	return (clear_text(arg, strndup(((complete_t *)data->data)->valid, len), result));
}

char *auto_complete(char *result, circular_dll_t *list, char *line)
{
	circular_dll_t *temp = list->go_to[NEXT];
	char **info = NULL;
	char *arg = NULL;

	if (strlen(result) == 0)
		return (result);
	info = my_str_to_word_array(result, ' ');
	arg = info[my_array_len(info) - 1];
	while (temp != list) {
		if (strncmp(arg, ((complete_t *)temp->data)->file, strlen(arg)) == 0) {
			((complete_t *)temp->data)->valid = strdup(((complete_t *)temp->data)->file);
		}
		else {
			((complete_t *)temp->data)->valid = "\0";
		}
		temp = temp->go_to[NEXT];
	}
	return (check_valid_path(list, result, arg));
}

int check_backslash_n(char *str)
{
	int i = 0;
	int mod = 0;

	while (str[i] != '\0') {
		if (str[i] == '\n') {
			mod = 1;
			i++;
			break;
		}
		i++;
	}
	if (mod == 0)
		return (0);
	return (i);
}

char* recons(char *buffer, char *result, int to_copy)
{
	int len = 0;
	int i = 0;

	len = my_strlen(result);
	buffer = malloc(sizeof(char) * len + 1);
	while (i != to_copy) {
		buffer[i] = result[i];
		i++;
	}
	buffer[i - 1] = '\0';
	i = 0;
	while (result[to_copy] != '\0') {
		result[i] = result[to_copy];
		i++;
		to_copy++;
	}
	result[i] = '\0';
	return (buffer);
}

char *get_next_line(int fd, circular_dll_t *list)
{
	char *buffer = calloc(3, sizeof(char) * 3 + 1);

	if (buffer == NULL)
		return (NULL);
	static char *result = NULL;
	static int passage = 0;
	int nbr = read(fd, buffer, 3);
	int to_copy = 0;

	buffer[nbr] = '\0';
	if (nbr != 3) {
		if (buffer[0] != 9)
			my_putstr(buffer);
		if (passage == 0) {
			result = strdup("\0");
		}
		if (buffer[0] == 9) {
			buffer = auto_complete(result, list, buffer);
			result[0] = '\0';
		}
		if (buffer[0] == 127) {
			buffer[0] = '\0';
			if (strlen(result) != 0) {
				write(1 , "\b \b", strlen("\b \b"));
				result[strlen(result) - 1] = '\0';
			}
		}
		if (nbr < 1)
			return (NULL);
		passage++;
		result = my_strdupcat(result, buffer);
		to_copy = check_backslash_n(result);
		if (to_copy != 0) {
			buffer = recons(buffer, result, to_copy);
			return (buffer);
		}
	}
	get_next_line(fd, list);
}

/*
** EPITECH PROJECT, 2018
** path
** File description:
** minishell
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "my_strings.h"
#include "linked_list.h"
#include "minishell.h"

static int find_brackets(char *arg)
{
	int in_brackets = 0;
	int have_brackets = false;

	for (int i = 0; i != my_strlen(arg); i++) {
		if ((arg)[i] == '[' && have_brackets == false) {
			have_brackets = true;
			in_brackets += 1;
		}
		if ((arg)[i] == ']')
			in_brackets -= 1;
	}
	if (have_brackets == true && in_brackets == 0)
		return (1);
	else
		return (0);
}

static int add_letter_to_list(circular_dll_t *my_letters, char letter)
{
	char *new_letter = malloc(sizeof(char));

	if (new_letter == NULL)
		return (84);
	*new_letter = letter;
	add_back(my_letters, new_letter);
	return (0);
}

static int add_sequence(circular_dll_t *my_letters, char a, char b)
{
	int start = a;
	int end = b;

	if (a > b) {
		start = b;
		end = a;
	}
	for (int i = start; i != end; i++) {
		if (add_letter_to_list(my_letters, (char)i) == 84)
			return (84);
	}
	return (0);
}

static int find_letter(circular_dll_t *my_letters, char *letters)
{
	int in_brackets = false;
	int error = 0;

	for (int i = 0; letters[i] != '\0' && letters[i] != ']'; i++) {
		if (in_brackets == true && letters[i] != '-')
			error = add_letter_to_list(my_letters, letters[i]);
		if (in_brackets == true && letters[i] == '-' && error != 84)
			error = add_sequence(my_letters, letters[i - 1], letters[i + 1]);
		if (letters[i] == '[')
			in_brackets = true;
		if (error == 84)
			return (84);
	}
	return (0);
}

int brackets(command_t *command)
{
	int have_brackets = false;
	circular_dll_t *my_letters = create_list();

	if (my_letters == NULL)
		return (84);
	for (int i = 1; command->node->data[i] != NULL; i++) {
		have_brackets = find_brackets(command->node->data[i]);
		if (have_brackets == false)
			continue;
		have_brackets = false;
		find_letter(my_letters, command->node->data[i]);
		loop_replace_arg(command, my_letters, command->node->data[i]);
		// free_list(my_letters);
	}
	return (0);
}

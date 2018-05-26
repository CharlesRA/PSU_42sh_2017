/*
** EPITECH PROJECT, 2017
** read_list.c
** File description:
** read a list
*/

#include <stdlib.h>
#include <stdio.h>
#include "str.h"
#include "linked_list.h"
#include "alias.h"
#include "shell.h"

void read_front(circular_dll_t *list)
{
	circular_dll_t *temp = list->go_to[NEXT];

	while (temp != list && temp != NULL) {
		printf("%s\n", ((complete_t*)temp->data)->file);
		temp = temp->go_to[NEXT];
	}
}

void read_back(circular_dll_t *list)
{
	circular_dll_t *temp = list->go_to[PREV];

	if (list->go_to[PREV] == NULL)
		return;
	while (temp != list)
		temp = temp->go_to[PREV];
}

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

void read_front(circular_dll_t *list)
{
	circular_dll_t *temp = list->go_to[NEXT];

	while (temp != list && temp != NULL) {
		printf("%s\n", ((alias_t*)temp->data)->value);
		printf("%s\n", ((alias_t*)temp->data)->alias);
		temp = temp->go_to[NEXT];
	}
}

void read_back(circular_dll_t *list)
{
	if (list->go_to[PREV] == NULL)
		return;
	circular_dll_t *temp = list->go_to[PREV];

	while (temp != list)
		temp = temp->go_to[PREV];
}

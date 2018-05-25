/*
** EPITECH PROJECT, 2017
** add_new_element.c
** File description:
** add an element to a list
*/

#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

circular_dll_t *create_list(void)
{
	circular_dll_t *root = malloc(sizeof(*root));

	if (root != NULL) {
		root->data = NULL;
		root->go_to[PREV] = root;
		root->go_to[NEXT] = root;
	}
	return (root);
}

int list_len(circular_dll_t *list)
{
	int count = 0;
	circular_dll_t *temp = list->go_to[NEXT];

	while (temp != list) {
		count++;
		temp = temp->go_to[NEXT];
	}
	return (count);
}

void read_front(circular_dll_t *list)
{
	circular_dll_t *temp = list->go_to[NEXT];

	while (temp != list) {
		printf("%s\n", (char *)temp->data);
		temp = temp->go_to[NEXT];
	}
}

void delete_element(circular_dll_t **element)
{
	element[0]->go_to[PREV]->go_to[NEXT] = element[0]->go_to[NEXT];
	element[0]->go_to[NEXT]->go_to[PREV] = element[0]->go_to[PREV];
	circular_dll_t *to_free = element[0];

	element[0] = element[0]->go_to[PREV];
	free(to_free);
}

int add_back(circular_dll_t *element, void *new_data)
{
	circular_dll_t *new_element = malloc(sizeof(*new_element));

	if (new_element == NULL)
		return (-1);
	if (new_element != NULL) {
		new_element->data = new_data;
		new_element->go_to[PREV] = element->go_to[PREV];
		new_element->go_to[NEXT] = element;
		element->go_to[PREV]->go_to[NEXT] = new_element;
		element->go_to[PREV] = new_element;
	}
	return (0);
}

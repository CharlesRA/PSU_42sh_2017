/*
** EPITECH PROJECT, 2017
** list.h
** File description:
** .h
*/

#ifndef LIST_H
#define LIST_H

enum e_dir
{
	PREV,
	NEXT,
	NBR_DIR
};

typedef struct s_circular_double_linked_list
{
	void *data;
	struct s_circular_double_linked_list *go_to[NBR_DIR];
} circular_dll_t;

int list_len(circular_dll_t *list);
void delete_element(circular_dll_t **element);
circular_dll_t *create_list(void);
void add_front(circular_dll_t *element, void *card);
int add_back(circular_dll_t *element, void *new_data);
void read_front(circular_dll_t *list);

#endif

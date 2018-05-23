/*
** EPITECH PROJECT, 2017
** my_sort_int_array
** File description:
** returns a pointer to a sorted int array
*/

void my_swap(int *a, int *b);

static int smallest_index(int *array, int size, int cursor)
{
	int min = cursor;

	for (int i = cursor + 1 ; i < size ; i++)
		if (array[i] < array[min])
			min = i;
	return (min);
}

int *my_sort_int_array(int *array, int size)
{
	int min;

	for (int cursor = 0 ; cursor < (size - 1) ; cursor++) {
		min = smallest_index(array, size, cursor);
		my_swap(&array[min], &array[cursor]);
	}
	return (array);
}

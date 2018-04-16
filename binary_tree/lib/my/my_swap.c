/*
** EPITECH PROJECT, 2017
** my_swap
** File description:
** swaps two integers
*/

void my_swap(int *a, int *b)
{
	int c = *a;

	*a = *b;
	*b = c;
}

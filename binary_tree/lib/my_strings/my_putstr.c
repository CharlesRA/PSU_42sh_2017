/*
** EPITECH PROJECT, 2017
** my_putstr
** File description:
** displays a char string
*/

#include <unistd.h>

int my_strlen(char const *str);

void my_putstr(char const *str)
{
	write(1, str, my_strlen(str));
}

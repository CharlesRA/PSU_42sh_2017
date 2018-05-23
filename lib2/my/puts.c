/*
** EPITECH PROJECT, 2017
** lib
** File description:
** puts
*/

#include "str.h"

int my_putstr(char const *str)
{
	int len = 0;

	len = my_strlen(str);
	return (write(1, str, len));
}

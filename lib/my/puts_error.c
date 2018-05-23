/*
** EPITECH PROJECT, 2018
** puts
** File description:
** error
*/

#include "str.h"

int my_putserr(char *str)
{
	int len = 0;

	len = my_strlen(str);
	return (write(2, str, len));
}

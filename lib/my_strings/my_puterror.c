/*
** EPITECH PROJECT, 2017
** my_puterror
** File description:
** prints a message on stderr
*/

#include <unistd.h>

int my_strlen(char const *str);

void my_puterror(char const *str)
{
	write(2, str, my_strlen(str));
}

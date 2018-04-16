/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** ut_error.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

Test (char_is_an_operator, char_is_an_operator1)
{
	int i = 1;
	int mod = 1;

	cr_assert(char_is_an_operator("#<;", &i, mod) == 1);
}

Test (operator, operator1)
{
	cr_assert(operator('<') == 1);
}

Test (error_pid, error2)
{
	int pid = -1;

	cr_assert(error_pid(pid) == 84);
}

Test (error_pid, error3)
{
	int pid = 1000;

	cr_assert(error_pid(pid) == 0);
}

Test (error_operator, error_operator2)
{
	cr_assert(error_operator("#") == 0);
}

/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** ut_error.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

Test (check_invalid_char, check_invalid_char1)
{
	cr_assert(check_invalid_char("PAT@H") == 1);
}

Test (check_invalid_char, check_invalid_char2)
{
	cr_assert(check_invalid_char("PAT_H") == 0);
}

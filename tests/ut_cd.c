/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** ut_cd.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

Test (find_home, find_home1)
{
	char *env[] = {"HOME=/Charles" , "PATH=dsf" , "PWD=ef" , NULL};

	cr_assert_str_eq(find_home(env) , "/Charles");
}

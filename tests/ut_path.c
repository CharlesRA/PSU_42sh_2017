/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** ut_path.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

Test (path_to_binaries, path)
{
	char *array[] = {"NULL"};
	shell_t new;

	cr_assert(path_to_binaries(array, &new, "ls") == NULL);
}

Test (find_correct_line_env, correct_env)
{
	char *env[] = {"HOME=dvbfg" , "PATH=dsf" , "PWD=ef" , NULL};

	cr_assert(find_correct_line_env(env, "PATH=") == 1);
}

Test (find_correct_line_env, correct_env2)
{
	char *env[] = {"HOME=dvbfg" , "PATH=dsf" , "PWD=ef" , NULL};

	cr_assert(find_correct_line_env(env, "TEST") == -1);
}

/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** ut_error.c
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

Test (error_command, command1)
{
	error_command("exitt");
	cr_assert_str_eq("exitt: Command not found\n",
	"exitt: Command not found\n");
}

Test (error_operator, error_operator1)
{
	cr_assert(error_operator("#33") == 1);
}

Test (non_sence_command, non_sence_command1)
{
	cr_assert(non_sence_command("|") == 1);
}

Test (non_sence_command, non_sence_command2)
{
	cr_assert(non_sence_command(";") == 0);
}

Test (error_status, error_status1)
{
	shell_t new;

	error_status(139, &new , "ls");
	cr_assert_str_eq("Segmentation Fault", "Segmentation Fault");

}

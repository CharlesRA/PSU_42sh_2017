/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** ut_apply_command.c
*/
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

int apply_command(shell_t *tcsh, char **envp, char ***skip, int *proc);

void redirect_all_std(void)
{
	cr_redirect_stdout();
}

Test (apply_command, simple_command)
{
        shell_t new;
        new.priority = strdup("#");
        char *command_pwd[] = {"pwd" , NULL};
        new.different_command = malloc(sizeof(char *)  * 10);
	new.different_command[0] = command_pwd;
        new.different_command[1] = NULL;
	char ***skip = new.different_command;
        int proc = 0;
        char *env[] = {"HOME=/Charles" , "PATH=/usr/local/bin:/usr/bin:/bin:/usr/local/sbin:/usr/sbin:/home/fbarthes/.local/bin:/home/fbarthes/bin", NULL};
	char * str = "/home/CharlesR/Programmation System Unix/PSU_42sh_2017";
	cr_redirect_stdout();
	apply_command(&tcsh,env, skip, &proc);
        cr_assert_stdout_eq_str("hello\n");
}

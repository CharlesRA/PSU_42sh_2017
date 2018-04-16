/*
** EPITECH PROJECT, 2018
** commands
** File description:
** header
*/

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "minishell.h"

int cmd_cd(char **cmd, command_t *command);
int cmd_env(char **cmd, command_t *command);
int cmd_setenv(char **cmd, command_t *command);
int cmd_unsetenv(char **cmd, command_t *command);
int cmd_exit(char **cmd, command_t *command);

char **add_line_to_env(char **envp, char *line, int n);
char **rm_line_to_env(char **envp, int n);
int change_env(command_t *command, char **cmd, int type);

int do_cd(char *cmd, command_t *command);

#endif

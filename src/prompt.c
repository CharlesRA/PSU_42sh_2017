/*
** EPITECH PROJECT, 2018
** display
** File description:
** all display functions
*/

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "minishell.h"
#include "str.h"
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

void *add_data(circular_dll_t *list, char *read)
{
	complete_t *data = malloc(sizeof(complete_t));

	data->file = strdup(read);
	data->valid = "\0";
	add_back(list, data);
}

void *generate_auto_complete(DIR *rep, circular_dll_t *list)
{
	struct dirent* data = NULL;
	circular_dll_t *temp = list->go_to[NEXT];

	while ((data = readdir(rep)) != NULL) {
		add_data(temp, data->d_name);
	}
}

void display_prompt(void)
{
	if (signal(SIGINT, prompt_int) == SIG_ERR)
		my_perror("signal");
	my_putstr("42sh: $> ");
}

void prepare_auto_complete(command_t *command, circular_dll_t *list)
{
	size_t size = 0;
	char **array;
	circular_dll_t *parsing = NULL;
	int i = 0;
	DIR *rep = NULL;

		while (command->env[i] != NULL) {
			if (my_strstr(command->env[i], "PATH=") == 1) {
				str_to_word_binaries(command->env[i], command);
				break;
			}
			i++;
		}
		// if (command->env[i] == NULL) {
		// 	command->return_value = 1;
		// 	error_command(command);
		// 	return (NULL);
		// }
		for (int i = 0; command->binaries[i] != NULL; i++) {
			rep = opendir(command->binaries[i]);
			generate_auto_complete(rep, list);
		}
		rep = opendir(".");
		generate_auto_complete(rep, list);
}

int prompt(command_t *command)
{
	char *cmd = NULL;
	int value = 0;
	size_t size = 0;
	circular_dll_t *list = create_list();

	do {
		prepare_auto_complete(command, list);
		
		if (cmd)
			free(cmd);
		if (isatty(0)) {
			display_prompt();
			cmd = get_next_line(0, list);
		}
		else {
			if (getline(&cmd, &size, stdin) == -1) {
				exit_shell(command->ret);
			}
			if (cmd[strlen(cmd) - 1] == '\n') {
				cmd[strlen(cmd) - 1] = '\0';
			}
		}
		if (cmd == NULL) {
			destroy_tab(command->env);
			exit_shell(command->ret);
		}
	} while (cmd[0] == 0);
	value = create_tree(&(command->node), cmd);
	free(cmd);
	return (value);
}

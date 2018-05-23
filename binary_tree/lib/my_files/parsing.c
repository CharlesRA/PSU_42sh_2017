/*
** EPITECH PROJECT, 2018
** parsing
** File description:
** parse file
*/

#include <stdlib.h>
#include "my_files.h"

char **parse_file(char const *filepath, char const *parsing)
{
	char *file = load_file_in_mem(filepath);
	char **parser = NULL;

	if (file == NULL)
		return (NULL);
	parser = my_str_to_word_array(file, parsing);
	free(file);
	return (parser);
}

char **parse_cmd(int fd, char const *parsing)
{
	char *cmd = get_next_line(fd);
	char **parser = NULL;

	if (cmd == NULL)
		return (NULL);
	parser = my_str_to_word_array(cmd, parsing);
	free(cmd);
	return (parser);
}

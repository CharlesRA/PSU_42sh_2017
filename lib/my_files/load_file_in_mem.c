/*
** EPITECH PROJECT, 2017
** load_file_in_mem
** File description:
** loads a file in memory and returns a pointer to this adress
*/

#include <unistd.h>
#include <fcntl.h>
#include "my_files.h"

char *load_file_in_mem(char const *filepath)
{
	int fd = open(filepath, O_RDONLY);
	char buff[1025];
	char *res = NULL;
	int nb = 0;

	if (fd == -1)
		return (NULL);
	while ((nb = read(fd, buff, 1024))) {
		buff[nb] = 0;
		res = mem_alloc(res, buff);
	}
	close(fd);
	return (res);
}

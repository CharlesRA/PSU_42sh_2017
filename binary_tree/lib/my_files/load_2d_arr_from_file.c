/*
** EPITECH PROJECT, 2017
** load_2d_arr_from_file
** File description:
** returns the rectangle contained in the file
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "my_files.h"

char **load_2d_arr_from_file(char const *filepath, int nb_rows, int nb_cols)
{
	char **arr = mem_alloc_2d_array(nb_rows, nb_cols);
	int fd = open(filepath, O_RDONLY);
	char *buff = malloc(nb_cols);

	if (!arr || !buff || !fd)
		return (0);
	for (int j = 0 ; j < nb_rows ; j++) {
		read(fd, buff, nb_cols);
		for (int i = 0 ; i < nb_cols ; i++)
			arr[j][i] = buff[i];
	}
	close(fd);
	free(buff);
	return (arr);
}

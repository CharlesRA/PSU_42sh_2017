/*
** EPITECH PROJECT, 2017
** my_strncpy
** File description:
** copies n chars from a string to another
*/

char *my_strncpy(char *dest, char const *src, int n)
{
	int i = 0;

	while (i < n) {
		dest[i] = src[i];
		if (src[i] == 0)
			break;
		i++;
	}
	return (dest);
}

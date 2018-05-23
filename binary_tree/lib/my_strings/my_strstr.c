/*
** EPITECH PROJECT, 2017
** my_strstr
** File description:
** returns a pointer to the first occurence of the searched string
*/

int my_strlen(char const *str);

char *my_strstr(char const *str, char const *to_find)
{
	int len = my_strlen(to_find);
	int cnt = 0;

	if (len == 0)
		return ((char *) str);
	for (int i = 0 ; str[i] ; i++) {
		if (str[i] == to_find[cnt])
			cnt++;
		else
			cnt = 0;
		if (cnt == len)
			return ((char *) &str[i - len + 1]);
	}
	return (0);
}

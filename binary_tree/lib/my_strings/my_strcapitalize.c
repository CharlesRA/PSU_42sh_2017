/*
** EPITECH PROJECT, 2017
** my_strcapitalize
** File description:
** capitalize every first letter of every word
*/

char *my_strlowcase(char *str);

char *my_strcapitalize(char *str)
{
	int i = 0;

	my_strlowcase(str);
	while (str[i] != '\0') {
		while (str[i] < 'a' || str[i] > 'z')
			i++;
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
		i++;
		while (str[i] >= 'a' && str[i] <= 'z')
			i++;
	}
	return (str);
}

/*
** EPITECH PROJECT, 2017
** my_strncmp
** File description:
** compare two strings from byte n
*/

int my_strlen(char const *str);

int my_strncmp(char const *s1, char const *s2, int n)
{
	int i = 0;
	int s1_len = my_strlen(s1) - 1;
	int s2_len = my_strlen(s2) - 1;
	int min_len = s1_len < s2_len ? s1_len : s2_len;

	while ((s1[i] == s2[i]) && i < n && i < min_len)
		i++;
	if (i == n)
		i--;
	if (s1[i] < s2[i])
		return (-1);
	else if (s1[i] > s2[i])
		return (1);
	return (0);
}

/*
** EPITECH PROJECT, 2017
** my_getnbr
** File description:
** returns an int given as a string
*/

static int make_num(char const *str, int start, int end)
{
	int output_num = 0;

	while (start < end) {
		output_num *= 10;
		output_num += (str[start] - '0');
		start++;
	}
	return (output_num);
}

int my_getnbr(char const *str)
{
	int i = 0;
	int pos = 1;
	int output;
	int start_num;

	if (!str)
		return (0);
	for (i = 0 ; str[i] == '-' || str[i] == '+' ; i++)
		if (str[i] == '-')
			pos *= -1;
	start_num = i;
	while (str[i] <= '9' && str[i] >= '0')
		i++;
	output = make_num(str, start_num, i);
	return (output * pos);
}

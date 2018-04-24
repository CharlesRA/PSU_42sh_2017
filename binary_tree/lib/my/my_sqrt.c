/*
** EPITECH PROJECT, 2017
** my_sqrt
** File description:
** returns the square root of nb
*/

int my_sqrt(int nb)
{
	if (nb <= 0)
		return (0);
	for (int i = 1 ; i <= nb ; i++)
		if (nb % i == 0 && nb / i == i)
			return (i);
	return (0);
}

/*
** EPITECH PROJECT, 2017
** my_pow_rec
** File description:
** returns nb to the power of p, recursively
*/

int my_pow_rec(int nb, int p)
{
	if (p < 0)
		return (0);
	if (p == 0)
		return (1);
	return (nb * my_pow_rec(nb, p - 1));
}

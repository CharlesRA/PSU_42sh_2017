/*
** EPITECH PROJECT, 2017
** my_is_prime
** File description:
** returns 1 if number is prime, and 0 if not
*/

int my_is_prime(int nb)
{
	int limit = nb / 2;

	if (nb < 2 || (nb % 2 == 0 && nb != 2))
		return (0);
	for (int i = 2 ; i < limit ; i++) {
		if (nb % i == 0)
			return (0);
	}
	return (1);
}

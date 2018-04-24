/*
** EPITECH PROJECT, 2017
** my_put_nbr
** File description:
** displays an int given as parameter
*/

void my_putchar(char c);

int my_put_nbr(int nb)
{
	int digit = nb % 10;
	int calc = nb / 10;

	if (nb < 0) {
		my_putchar('-');
		digit *= -1;
		calc *= -1;
	}
	if (calc != 0)
		my_put_nbr(calc);
	my_putchar(digit + '0');
	return (0);
}

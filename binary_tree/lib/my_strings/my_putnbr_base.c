/*
** EPITECH PROJECT, 2017
** my_putnbr_base
** File description:
** displays a decimal number into a number in given base
*/

void my_putchar(char c);

int my_strlen(char const *str);

int my_putnbr_base(int nb, char const *base)
{
	int len = my_strlen(base);
	int rec = nb / len;
	int calc = nb % len;

	if (nb < 0) {
		my_putchar('-');
		rec *= -1;
		calc *= -1;
	}
	if (rec != 0)
		my_putnbr_base(rec, base);
	my_putchar(base[calc]);
	return (0);
}

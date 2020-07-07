static void			ft_putlong_fd(long n, int fd)
{
	int		i;
	char	a[22];

	if (n == 0)
		write(fd, "0", 1);
	else
	{
		i = ft_nb_digit_custo(n, 10);
		a[i] = 0;
		while (i-- > 0 && n)
		{
			a[i] = n % 10 + '0';
			n /= 10;
		}
		write(fd, a, ft_strlen(a));
	}
}
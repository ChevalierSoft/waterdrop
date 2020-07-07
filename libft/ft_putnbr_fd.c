/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:28:19 by dait-atm          #+#    #+#             */
/*   Updated: 2019/11/18 16:08:06 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nb_digit_custo(int n)
{
	int nbc;

	if (!n)
		return (1);
	nbc = 0;
	while (n)
	{
		n /= 10;
		nbc++;
	}
	return (nbc);
}

void		ft_putnbr_fd(int n, int fd)
{
	char			a[12];
	int				i;

	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n == 0)
		write(fd, "0", 1);
	else
	{
		i = ft_nb_digit_custo(n);
		if (n < 0)
		{
			n = -n;
			a[0] = '-';
			i++;
		}
		a[i] = 0;
		while (i > 0 && n)
		{
			a[i - 1] = n % 10 + '0';
			n /= 10;
			i--;
		}
		write(fd, a, ft_strlen(a));
	}
}

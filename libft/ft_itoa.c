/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:21:59 by dait-atm          #+#    #+#             */
/*   Updated: 2019/11/13 20:08:53 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nb_digit_custo(int n)
{
	int nbc;

	nbc = 0;
	if (n > 0)
		nbc--;
	while (n)
	{
		n /= 10;
		nbc++;
	}
	return (nbc);
}

char		*ft_itoa(int n)
{
	long			m;
	unsigned char	nbc;
	unsigned char	tm;
	char			a[12];

	if (!n)
		return (ft_strdup("0"));
	m = n;
	tm = 0;
	if (n < 0)
	{
		m *= -1;
		a[tm++] = (char)'-';
	}
	nbc = ft_nb_digit_custo(n);
	while (m)
	{
		a[nbc] = m % 10 + 48;
		m /= 10;
		tm++;
		nbc--;
	}
	a[tm] = 0;
	return (ft_strdup(a));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 19:58:59 by dait-atm          #+#    #+#             */
/*   Updated: 2019/11/19 23:39:55 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_print_hex(unsigned long v, int nbd)
{
	unsigned long	tab[nbd];
	long			j;
	unsigned char	qwe;

	j = 0;
	while (j < nbd)
		tab[j++] = 0;
	j--;
	while ((v > 0) && (j || nbd == 1))
	{
		tab[j] = v % 16;
		v /= 16;
		j--;
	}
	j = 1;
	while (j < nbd)
	{
		if (tab[j] >= 10)
			qwe = (tab[j] - 10 + 'a');
		else
			qwe = (tab[j] += '0');
		write(1, &qwe, 1);
		j++;
	}
}

static int		ft_aff_oct(void *addr, unsigned int size)
{
	int		cpt;
	int		flagou;
	int		sp;

	sp = 0;
	flagou = 0;
	cpt = 16;
	if (size < 16)
		cpt = size;
	while (cpt)
	{
		ft_print_hex((unsigned long)((char*)addr), 3);
		if (flagou)
		{
			write(1, " ", 1);
			flagou = 0;
			sp++;
		}
		else
			flagou++;
		addr++;
		cpt--;
		sp += 2;
	}
	return (sp);
}

static void		ft_aff_msg(void *addr, int nbr)
{
	char	*c;

	c = (char *)addr;
	while (nbr)
	{
		c = (char *)addr;
		if ((*c >= ' ' && *c <= '~'))
			write(1, &(*c), 1);
		else if (*c == 0)
		{
			write(1, "\x1B[31m", 5);
			write(1, ".", 1);
			write(1, "\x1B[0m", 5);
		}
		else
			write(1, ".", 1);
		addr++;
		nbr--;
	}
}

void			*ft_print_memory(void *addr, size_t size)
{
	size_t		aerosol;

	aerosol = 0;
	while (size > 16)
	{
		ft_print_hex((unsigned long)addr, 16);
		write(1, ": ", 2);
		ft_aff_oct(addr, size);
		ft_aff_msg(addr, 16);
		write(1, "\n", 1);
		size -= 16;
		addr += 16;
	}
	if (size)
	{
		ft_print_hex((unsigned long)addr, 16);
		write(1, ": ", 2);
		aerosol = 40 - ft_aff_oct(addr, size);
		while (aerosol-- > 0)
			write(1, " ", 1);
		ft_aff_msg(addr, size);
	}
	return (addr);
}

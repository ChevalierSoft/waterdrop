/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 22:24:31 by dait-atm          #+#    #+#             */
/*   Updated: 2020/07/14 22:24:37 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "waterdrop.h"

void	print(char *s)
{
	write(1, s, ft_strlen(s));
}

void	printr(char *s)
{
	print(MAG);
	print(s);
	print(RST);
}

void	help(void)
{
	printr("help\n");
}

void	alert(void)
{
	print(CYN "alert\n" RST);
}

int		ft_aff_file(char *name)
{
	int		fdv;
	char	buf[1];
	char	res;

	fdv = open(name, O_RDONLY);
	while ((res = read(fdv, buf, 1)) > 0)
	{
		write(1, buf, 1);
	}
	write(1, "\n", 1);
	close(fdv);
	return (0);
}

void	aff_meta(t_meta *meta)
{
	printf("sR : %s\n", meta->str_r);
	printf("R  : ww : %d : wh  : %d\n", meta->ww, meta->wh);
	printf("NO : %s\n", meta->path_n);
	printf("SO : %s\n", meta->path_s);
	printf("EA : %s\n", meta->path_e);
	printf("WE : %s\n", meta->path_w);
	printf("SP : %s\n", meta->path_sp);
	printf("F  : %s\n", meta->path_f);
	printf("C  : %s\n", meta->path_c);
}

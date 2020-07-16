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

void		ft_aff_map(int **map, t_pos *mapsize, t_pos *ppl)
{
	int i;
	int j;

	j = 0;
	while (j < mapsize->y)
	{
		i = 0;
		while (i < mapsize->x)
		{
			if (i == ppl->x && j == ppl->y)
			{
				printf(YEL "%c " RST, ppl->o);
				i++;
			}
			else
			{
				if (map[j][i] == 0)
					printf(BLK "%d " RST, map[j][i++]);
				else if (map[j][i] == 1)
					printf(MAG "%d " RST, map[j][i++]);
				else if (map[j][i] == 'x')
					printf(CYN "%c " RST, map[j][i++]);
				else if (map[j][i] == '+')
					printf(GRN "%c " RST, map[j][i++]);
				else if (map[j][i] == ' ')
					printf(WHT "%c " RST, map[j][i++]);
				else
					printf(YEL "%d " RST, map[j][i++]);
			}
		}
		printf("\n");
		j++;
	}
}

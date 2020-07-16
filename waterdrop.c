/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waterdrop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:41:04 by dait-atm          #+#    #+#             */
/*   Updated: 2020/07/15 14:41:11 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "waterdrop.h"

static int	set_new_puddle(int **nmap, int px, int py, int *puddles)
{
	if (nmap[py][px] == ' ')
		return (-2);
	if (nmap[py][px] == 0 || nmap[py][px] == 2)
	{
		nmap[py][px] = '+';
		(*puddles)++;
	}
	return (0);
}

static int	water_puddle(int **nmap, t_pos *mapsize, t_pos *pudpos)
{
	int puddles;

	puddles = 0;
	if (!pudpos->y || !pudpos->x || pudpos->y == mapsize->y - 1
		|| pudpos->x == mapsize->x - 1)
		return (-1);
	if (set_new_puddle(nmap, pudpos->x, pudpos->y - 1, &puddles) < 0)
		return (-1);
	if (set_new_puddle(nmap, pudpos->x + 1, pudpos->y, &puddles) < 0)
		return (-1);
	if (set_new_puddle(nmap, pudpos->x, pudpos->y + 1, &puddles) < 0)
		return (-1);
	if (set_new_puddle(nmap, pudpos->x - 1, pudpos->y, &puddles) < 0)
		return (-1);
	nmap[pudpos->y][pudpos->x] = 'x';
	return (puddles);
}

int			waterdrop_htm(t_pos *pudpos, t_pos *mapsize, int **cmap, int **nmap)
{
	int err;
	int puddles;

	puddles = 0;
	while (pudpos->y < mapsize->y)
	{
		pudpos->x = 0;
		while (pudpos->x < mapsize->x)
		{
			if (cmap[pudpos->y][pudpos->x] == '+')
			{
				err = water_puddle(nmap, mapsize, pudpos);
				if (err < 0)
				{
					return (err);
				}
				(puddles) += err;
			}
			pudpos->x++;
		}
		pudpos->y++;
	}
	return (puddles);
}

int			waterdrop_loop(int **cmap, int **nmap, t_pos *mapsize, t_pos *ppl)
{
	t_pos	pudpos;
	int		puddles;

	pudpos.x = 0;
	pudpos.y = 0;
	puddles = 1;
	while (puddles > 0)
	{
		puddles = 0;
		pudpos.y = 0;
		if ((puddles = waterdrop_htm(&pudpos, mapsize, cmap, nmap)) < 0)
			break ;
		remove_2d_array(&cmap, mapsize->y);
		if (!(cmap = dup_array(nmap, mapsize->x, mapsize->y)))
		{
			print("Error\nNot enough memory for cmap\n");
			return (-37);
		}
		ft_aff_map(nmap, mapsize, ppl);
	}
	remove_2d_array(&cmap, mapsize->y);
	remove_2d_array(&nmap, mapsize->y);
	return (puddles);
}

int			waterdrop(int **map, t_pos *mapsize, t_pos *ppl)
{
	int **cmap;
	int **nmap;
	int err;

	if (!(cmap = dup_array(map, mapsize->x, mapsize->y)))
	{
		print("Error\nNot enough memory for cmap\n");
		return (-36);
	}
	if (!(nmap = dup_array(map, mapsize->x, mapsize->y)))
	{
		print("Error\nNot enough memory for nmap\n");
		return (-37);
	}
	cmap[ppl->y][ppl->x] = '+';
	err = waterdrop_loop(cmap, nmap, mapsize, ppl);
	return (err);
}

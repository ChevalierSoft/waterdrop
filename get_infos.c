/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 08:35:32 by dait-atm          #+#    #+#             */
/*   Updated: 2020/07/15 08:35:38 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "waterdrop.h"

/*
** in set_r()
** need to test meta->ww and meta->wh < mlx_get_screen_size
*/

int			set_r(t_meta *meta)
{
	int i;

	i = 0;
	if ((meta->ww = ft_atoi(meta->str_r)) <= 3)
	{
		print("Error\nWrong width resolution in .cub file\n");
		return (-1);
	}
	while (meta->str_r[i] != ' ')
		i++;
	i++;
	if ((meta->wh = atoi(meta->str_r + i)) <= 3)
	{
		print("Error\nWrong height resolution in .cub file\n");
		return (-2);
	}
	return (0);
}

static int	ledgit_square(char c, t_pos *ppl, int vx, int mapy)
{
	if (c == '0' || c == '1' || c == '2' || c == ' ')
		return (1);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (ppl->x != -1 || ppl->y != -1)
			return (ERROR_DOUBLE_SPAWN);
		ppl->x = vx;
		ppl->y = mapy - 1;
		ppl->o = c;
		return (1);
	}
	else
		return (-1);
}

static int	ft_get_map_xy(char *l, t_pos *mapsize, t_pos *ppl)
{
	int		vx;

	vx = 0;
	while (*l)
	{
		if (ledgit_square(*l, ppl, vx, mapsize->y) > 0)
			vx++;
		else
		{
			print("Error\nWrong character for the map in .cub file\n");
			return (ERROR_WRONG_CHAR);
		}
		l++;
	}
	if (mapsize->x < vx)
		mapsize->x = vx;
	mapsize->y++;
	return (0);
}

int			ft_map_found(t_intel *it, char *l)
{
	int err;
	int gnl;

	it->map_size->y++;
	err = ft_get_map_xy(l, it->map_size, it->ppl);
	free(l);
	if (err < 0)
		return (ERROR_WRONG_CHAR);
	while (err >= 0 && (gnl = get_next_line(it->fd, &l)) > 0)
	{
		err = ft_get_map_xy(l, it->map_size, it->ppl);
		free(l);
	}
	if (gnl == GNL_EOF)
		free(l);
	if (it->ppl->x == -1)
	{
		err = ERROR_NO_SPAWN;
		print("Error\nNo spawn in .cub file\n");
	}
	return (err);
}

int			get_infos(t_intel *it)
{
	char	*l;
	int		err;
	int		gnl;

	l = NULL;
	err = 0;
	while (err >= 0 && (gnl = get_next_line(it->fd, &l)) > 0)
	{
		if ((err = reddit(it, l)) == MAP_FOUND)
			break ;
		free(l);
	}
	if (err == MAP_FOUND)
	{
		err = ft_map_found(it, l);
	}
	return (err);
}

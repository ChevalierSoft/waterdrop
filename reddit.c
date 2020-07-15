/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reddit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:25:49 by dait-atm          #+#    #+#             */
/*   Updated: 2020/07/15 14:25:54 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "waterdrop.h"

static int	dup4meta(char **s, char *l, int *map_offset, int d)
{
	(*map_offset) += ft_strlen(l) + d + 1;
	if (!((*s) = ft_strdup(l)))
	{
		print("Error\nNot enough RAM for t_meta strings\n");
		return (-1);
	}
	return (0);
}

int			r_part3(t_intel *it, char *l)
{
	if (ft_memchr(" 012NSEW", *l, 8))
	{
		if (!(it->meta->str_r && it->meta->path_n && it->meta->path_s
			&& it->meta->path_e && it->meta->path_w && it->meta->path_sp
			&& it->meta->path_f && it->meta->path_c))
		{
			print("Error\nLake of intel before the map in .cub file\n");
			return (ERROR_INFO);
		}
		return (MAP_FOUND);
	}
	else
	{
		print("Error\nWrong line in .cub file\n");
		return (-3);
	}
	return (0);
}

int			r_part2(t_intel *it, char *l, int *err)
{
	if (!ft_strncmp(l, "EA ", 3))
		*err = dup4meta(&it->meta->path_e, l + 3, &it->map_offset, 3);
	else if (!ft_strncmp(l, "WE ", 3))
		*err = dup4meta(&it->meta->path_w, l + 3, &it->map_offset, 3);
	else if (!ft_strncmp(l, "S ", 2))
		*err = dup4meta(&it->meta->path_sp, l + 2, &it->map_offset, 2);
	else if (!ft_strncmp(l, "F ", 2))
		*err = dup4meta(&it->meta->path_f, l + 2, &it->map_offset, 2);
	else if (!ft_strncmp(l, "C ", 2))
		*err = dup4meta(&it->meta->path_c, l + 2, &it->map_offset, 2);
	else
		*err = r_part3(it, l);
	return (*err);
}

int			r_part1(t_intel *it, char *l)
{
	int err;

	err = 0;
	if (!l || !it->meta)
	{
		print("Error\nDamaged memory\n");
		return (ERROR_DAMAGED_MEMORY);
	}
	else if (!l[0])
		it->map_offset++;
	else if (!ft_strncmp(l, "R ", 2))
	{
		err = dup4meta(&it->meta->str_r, l + 2, &it->map_offset, 2);
		if ((err = set_r(it->meta)) < 0)
			return (err);
	}
	else if (!ft_strncmp(l, "NO ", 3))
		err = dup4meta(&it->meta->path_n, l + 3, &it->map_offset, 3);
	else if (!ft_strncmp(l, "SO ", 3))
		err = dup4meta(&it->meta->path_s, l + 3, &it->map_offset, 3);
	else
		err = r_part2(it, l, &err);
	return (err);
}

int			reddit(t_intel *it, char *l)
{
	int err;

	err = r_part1(it, l);
	return (err);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 07:18:57 by dait-atm          #+#    #+#             */
/*   Updated: 2020/07/11 07:19:05 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "waterdrop.h"

void	zero(int **map, int mx, int my, char zero)
{
	int i;
	int j;

	j = 0;
	while (j < my)
	{
		i = 0;
		while (i < mx)
			map[j][i++] = zero;
		j++;
	}
}

int		**init_2d_array(int mx, int my)
{
	int i;
	int j;
	int **map;

	map = malloc(sizeof(int *) * my);
	i = 0;
	j = 0;
	while (j < my)
	{
		map[j++] = malloc(sizeof(int) * mx);
	}
	zero(map, mx, my, ' ');
	return (map);
}

void	remove_2d_array(int ***map, int my)
{
	int j;

	if (!(*map))
		return ;
	j = 0;
	while (j < my)
	{
		free((*map)[j++]);
	}
	free(*map);
	(*map) = NULL;
}

int		**dup_array(int **map, int mx, int my)
{
	int i;
	int j;
	int **w;

	if (!map)
		return (NULL);
	if (!(w = init_2d_array(mx, my)))
		return (NULL);
	j = 0;
	while (j < my)
	{
		i = 0;
		while (i < mx)
		{
			w[j][i] = map[j][i];
			i++;
		}
		j++;
	}
	return (w);
}

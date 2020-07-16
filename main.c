/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 22:26:37 by dait-atm          #+#    #+#             */
/*   Updated: 2020/07/14 22:26:48 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "waterdrop.h"

static int	**ft_get_map(int fd, t_pos *mapsize)
{
	int		i;
	int		j;
	int		**map;
	char	buf[1];

	i = 0;
	j = 0;
	map = init_2d_array(mapsize->x, mapsize->y);
	while (read(fd, buf, 1) > 0)
	{
		if (*buf == '1' || *buf == '2' || *buf == '0')
			map[j][i++] = c2i(*buf);
		else if (*buf == ' ')
			map[j][i++] = ' ';
		else if (*buf == 'N' || *buf == 'E' || *buf == 'S' || *buf == 'W')
			map[j][i++] = 0;
		else if (i == mapsize->x || (*buf == '\n'))
		{
			j++;
			i = 0;
		}
	}
	close(fd);
	return (map);
}

static void	ft_apply_map_offset(t_intel *it)
{
	char buf[it->map_offset];

	read(it->fd, buf, it->map_offset);
}

static int	game_redirection(t_intel **it, int wp)
{
	if (wp < 0)
	{
		if (wp >= -2)
			print(RED "water leaks in the map\n" RST);
	}
	else
		print(CYN "the map looks ledgit\n" RST);
	remove_intel(it);
	return (wp);
}

int			main(int argc, char **argv)
{
	t_intel *it;

	print(CYN "\n. o O 🌊 WATERDROP 🌊 O o .\n\n" RST);
	it = create_intel();
	if (argc < 2)
		it->filename = strdup("maps/info.cub");
	else
		it->filename = strdup(argv[1]);
	if ((it->fd = open(it->filename, O_RDONLY)) < 0)
		flush_quit("Error\nWrong .cub file path\n", &it, -1);
	if (get_infos(it) < 0)
	{
		close(it->fd);
		flush_quit("", &it, -3);
	}
	close(it->fd);
	if ((it->fd = open(it->filename, O_RDONLY)) < 0)
		flush_quit("Error\nWrong .cub file path\n", &it, -4);
	ft_apply_map_offset(it);
	it->map = ft_get_map(it->fd, it->map_size);
	ft_aff_map(it->map, it->map_size, it->ppl);
	game_redirection(&it, waterdrop(it->map, it->map_size, it->ppl));
	return (0);
}

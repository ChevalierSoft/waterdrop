#include "waterdrop.h"

void	ft_init_pos(t_pos *p, int nx, int ny, char no)
{
	p->x = nx;
	p->y = ny;
	p->o = no;
}

int		**ft_get_map(int fd, t_pos mapsize)
{
	int		i;
	int		j;
	int		**map;
	char	buf[1];

	i = 0;
	j = 0;
	map = init_2d_array(mapsize.x, mapsize.y);
	while (read(fd, buf, 1) > 0)
	{
		if (*buf == '1' || *buf == '2' || *buf == '0')
			map[j][i++] = c2i(*buf);
		else if (*buf == ' ')
			map[j][i++] = ' ';
		else if (*buf == 'N' || *buf == 'E' || *buf == 'S' || *buf == 'W')
			map[j][i++] = 0;
		else if (i == mapsize.x || (*buf == '\n'))
		{
			j++;
			i = 0;
		}
	}
	printf("\n");
	close(fd);
	return (map);
}

int		main(int argc, char** argv)
{
	printf(CYN "\n. o O 🌊 WATERDROP 🌊 O o .\n\n" RST);

	int fd;
	char *name;
	int **map;
	int err;
	t_pos mapsize;
	t_pos ppl;
	int map_offset;
	t_meta *meta;
	
	if (argc < 2)
		name = strdup("maps/info.cub");
	else
		name = strdup(argv[1]);

	ft_init_pos(&mapsize, 0, 0, 'x');
	ft_init_pos(&ppl, -1, -1, 'p');

	if ((fd = open(name, O_RDONLY)) < 0)
	{
		print("wrong .cub file path\n");
		print("wrong .cub file path\n");
		return (-1);
	}

	if (!(meta = meta_init()))
		return (-2);

	map_offset = 0;
	if (get_infos(meta, fd, &map_offset, &mapsize, &ppl))
	{
		remove_meta(&meta);
		print("wrong .cub file path\n");
		close(fd);
		free(name);
		return (-3);
	}
	close(fd);

	// maintenant on a l'intel

	if ((fd = open(name, O_RDONLY)) < 0)
	{
		print("wrong .cub file path\n");
		remove_meta(&meta);
		free(name);
		return (-4);
	}
	free(name);

	char pute[map_offset];
	read(fd, pute, map_offset);

	map = ft_get_map(fd, mapsize);
	ft_aff_map(map, mapsize, &ppl);
	err = waterdrop(map, mapsize, &ppl);
	if (err < 0)
		printf(RED "water leaks in the map\n" RST);
	else
		printf(CYN "the map looks ledgit\n" RST);
	remove_2d_array(map, mapsize.y);
	remove_meta(&meta);
	return (0);
}

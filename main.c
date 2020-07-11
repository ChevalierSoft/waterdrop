#include "waterdrop.h"

void	ft_init_pos(position_t *p, int _x, int _y, char _o)
{
	p->x = _x;
	p->y = _y;
	p->o = _o;
}

int		**ft_get_map(int fd, position_t mapsize)
{
	int i;
	int j;
	int **map;
	char buf[1];
	char res;

	i = 0;
	j = 0;
	map = init_2Darray(mapsize.x, mapsize.y);

	while ((res = read(fd, buf, 1)) > 0)
	{
		if (*buf == '1' || *buf == '2' || *buf == '0')
		{
			map[j][i++] = c2i(*buf);
		}
		else if (*buf == ' ')
		{
			map[j][i++] = ' ';
		}
		else if (*buf == 'N' || *buf == 'E' || *buf == 'S' || *buf == 'W')
		{
			map[j][i++] = 0;
		}
		else if (i == mapsize.x || (*buf == '\n')) // && !endl
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
	position_t mapsize;
	position_t ppl;
	int straff;
	meta_t *meta;

	
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

	straff = 0;
	if (get_infos(meta, fd, &straff, &mapsize, &ppl))
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

	char pute[straff];
	read(fd, pute, straff);

	map = ft_get_map(fd, mapsize);
	ft_aff_map(map, mapsize, &ppl);
	err = waterdrop(map, mapsize, &ppl);
	if (err < 0)
		printf(RED "water leaks in the map\n" RST);
	else
		printf(CYN "the map looks ledgit\n" RST);
	del_2Darray(map, mapsize.y);
	
	remove_meta(&meta);
	return(0);
}

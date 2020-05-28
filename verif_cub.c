#include "waterdrop.h"

void	zero(int **map, int mx, int my)
{
	int i;
	int j;

	j = 0;
	while (j < my)
	{
		i = 0;
		while (i < mx)
			map[j][i++] = 0;
		j++;
	}
}

int	**init_2Darray(int mx, int my)
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
	zero(map, mx, my);
	return (map);
}

void	del_2Darray(int **map, int my)
{
	int j;

	j = 0;
	while (j < my)
	{
		free(map[j++]);
	}
	free(map);
}

int **dup_array(int **map, int mx, int my)
{
	int i;
	int j;
	int **w;

	w = init_2Darray(mx, my);
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

int	c2i(char c)
{

	return (c - '0');
}

int	ft_aff_file(char *name)
{
	int fdv;
	char buf[1];
	char res;

	fdv = open(name, O_RDONLY);
	while ((res = read(fdv, buf, 1)) > 0)
	{
		write(1, buf, 1);
	}
	write(1, "\n", 1);
	close(fdv);
	return (0);
}

int	ft_aff_map(int **map, position_t mapsize, position_t *ppl)
{
	int i;
	int j;

	j = 0;
	while (j < mapsize.y)
	{
		i = 0;
		while (i < mapsize.x)
		{
			if (i == ppl->x && j == ppl->y)
				printf(YEL "%c " RST, ppl->o, i++);
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

int	ledgit_square(char c, position_t *ppl, int vx, int mapY)
{
	if (c == '0' || c == '1' || c == '2' || c == ' ')
		return (1);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (ppl->x != -1 || ppl->y != -1)
			return (0);
		ppl->x = vx;
		ppl->y = mapY - 1;
		ppl->o = c;
		return (1);
	}
	else
		return (0);
}

int	ft_get_mapXY(char *name, position_t *mapsize, position_t *ppl)
{
	int fdv;
	unsigned char buf[1];
	char res;
	int vx;
	int endl;

	mapsize->x = 0;
	mapsize->y = 1;
	endl = 1;
	vx = 0;
	if ((fdv = open(name, O_RDONLY)) < 0)
	{
		printf("probleme d'ouverture du fichier\n");
		return (-1);
	}
	while ((res = read(fdv, buf, 1)) > 0)
	{
		if (buf[0] == '\n')
		{
			if (mapsize->x < vx)
				mapsize->x = vx;
			vx = 0;
			if (!endl)
			{
				(mapsize->y)++;
				endl = 1;
			}
		}
		else if (ledgit_square(*buf, ppl, vx, mapsize->y))
		{
			endl = 0;
			vx++;
		}
		else
		{
			printf("caractere inaproprié\n");
			return (-2);
		}
	}
	close(fdv);
	return (mapsize->y);
}

int	ft_verif_map(char *name, position_t *mapsize, position_t *ppl)
{
	int err;

	err = ft_get_mapXY(name, mapsize, ppl);
	if (err == -1)
	{
		printf("error : code %d\n", err);
		return (-1);
	}
	if (mapsize->x < 3 || mapsize->y < 3 || ppl->x < 1 || ppl->y < 1)
	{
		printf("error : map too small\n");
		return (-2);
	}
	printf("mapsize : (%d, %d)\n", mapsize->x, mapsize->y);
	printf("ppl->x = %d : ppl->y = %d : ppl->o = %c\n", ppl->x, ppl->y, ppl->o);
	return (0);
}

int	**ft_get_map(char *name, position_t mapsize)
{
	int i;
	int j;
	int **map;
	int fdv;
	char buf[1];
	char res;
	int endl;

	i = 0;
	j = 0;
	endl = 1;
	map = init_2Darray(mapsize.x, mapsize.y);
	fdv = open(name, O_RDONLY);
	// I may use get_next_line() to gain some speed
	while ((res = read(fdv, buf, 1)) > 0)
	{
		if (*buf == '1' || *buf == '2' || *buf == '0')
		{
			map[j][i++] = c2i(*buf);
			endl = 0;
		}
		else if (*buf == ' ')
		{
			map[j][i++] = ' ';
			endl = 0;
		}
		else if (*buf == 'N' || *buf == 'E' || *buf == 'S' || *buf == 'W')
		{
			map[j][i++] = 0;
			endl = 0;
		}
		if (i >= mapsize.x || (*buf == '\n' && !endl))
		{
			j++;
			i = 0;
			endl = 1;
		}
	}
	printf("\n");
	close(fdv);
	return (map);
}

int	main(int argc, char** argv)
{
	char *name;
	position_t mapsize;
	int **map;
	int err;
	position_t ppl;

	if (argc < 2)
		name = strdup("maps/map2.cub");
	else
		name = argv[1];
	ppl.x = -1;
	ppl.y = -1;
	if (ft_verif_map(name, &mapsize, &ppl))
		return (0);
	map = ft_get_map(name, mapsize);
	// ft_aff_map(map, mapsize, &ppl);
	err = waterdrop(map, mapsize, &ppl);
	if (err < 0)
		printf(RED "water leaks in the map\n" RST);
	else
		printf(CYN "the map looks ledgit\n" RST);
	del_2Darray(map, mapsize.y);
	return(0);
}
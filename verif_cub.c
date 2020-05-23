#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct	position_s
{
	int x;
	int y;
	int o;
}				position_t;

typedef struct	waterDrop_s
{
	int px;
	int py;
	int e;
}				waterDrop_t;

void	help()
{

	write(1, "help\n", 5);
}

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

int	ft_aff_map(int **map, int mapX, int mapY, position_t *ppl)
{
	int i;
	int j;

	j = 0;
	while (j < mapY)
	{
		i = 0;
		while (i < mapX)
		{
			if (i == ppl->x && j == ppl->y)
				printf("%c ", ppl->o, i++);
			else
				printf("%d ", map[j][i++]);
		}
		printf("\n");
		j++;
	}
}

int	ledgit_square(char c, position_t *ppl, int vx, int mapY)
{
	if (c == '0' || c == '1' || c == '2')
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

int	ft_get_mapXY(char *name, int *mapX, int *mapY, position_t *ppl)
{
	int fdv;
	unsigned char buf[1];
	char res;
	int vx;

	*mapX = 0;
	*mapY = 1;
	vx = 0;
	if ((fdv = open(name, O_RDONLY)) < 0)
		return (-1);
	while ((res = read(fdv, buf, 1)) > 0)
	{
		if (buf[0] == '\n')
		{
			if (*mapX < vx)
				*mapX = vx;
			vx = 0;
			(*mapY)++;
		}
		else if (ledgit_square(*buf, ppl, vx, *mapY))
			vx++;
		else if (*buf == ' ')
			;
		else
			return (-2);
	}
	close(fdv);
	return (*mapY);
}

int	ft_verif_map(char *name, int *mapX, int *mapY, position_t *ppl)
{
	int err;

	err = ft_get_mapXY(name, mapX, mapY, ppl);
	if (*mapX < 3 || *mapY < 3 || ppl->x < 1 || ppl->y < 1)
	{
		printf("error : code %d\n", err);
		return (1);
	}
	printf("mapX = %d\n", *mapX);
	printf("mapY = %d\n", *mapY);
	printf("ppl->x = %d : ppl->y = %d : ppl->o = %c\n", ppl->x, ppl->y, ppl->o);
	return (0);
}

int	**ft_get_map(char *name, int mapX, int mapY)
{
	int i;
	int j;
	int **map;
	int fdv;
	char buf[1];
	char res;

	i = 0;
	j = 0;
	map = init_2Darray(mapX, mapY);
	fdv = open(name, O_RDONLY);
	// May use get_next_line() to gain some speed
	while ((res = read(fdv, buf, 1)) > 0)
	{
		if (*buf == '1' || *buf == '2' || *buf== '0')
		{
			map[j][i++] = c2i(*buf);
		}
		else if (*buf == 'N' || *buf == 'E' || *buf == 'S' || *buf == 'W')
		{
			map[j][i++] = 0;
		}
		if (i >= mapX)
		{
			j++;
			i = 0;
		}
	}
	printf("\n");
	close(fdv);
	return (map);
}

int propagation(int **map, int mx, int my, position_t *ppl)
{
	int **wmap;
	int puddle;
	
	wmap = dup_array(map, mx, my);
	puddle = 0;

	write(1, "yeet\n", 5);
	del_2Darray(wmap, my);
}

int	main(void)
{
	char *name = "maps/map3.cub";
	int mapX;
	int mapY;
	int **map;
	position_t ppl;

	ppl.x = -1;
	ppl.y = -1;
	if (ft_verif_map(name, &mapX, &mapY, &ppl))
		return (0);
	map = ft_get_map(name, mapX, mapX);
	ft_aff_map(map, mapX, mapY, &ppl);
	propagation(map, mapX, mapY, &ppl);
	del_2Darray(map, mapY);
	return(0);
}
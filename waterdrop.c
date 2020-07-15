#include "waterdrop.h"
//#include <windows.h>

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

static int	set_new_puddle(int **nmap, int px, int py, int *puddles)
{
	// if there is a hole in the inside
	if (nmap[py][px] == ' ')
		return (-2);
	// floor or objects
	if (nmap[py][px] == 0 || nmap[py][px] == 2)
	{
		nmap[py][px] = '+';
		(*puddles)++;
	}
	return (0);
}

static int	water_puddle(int **nmap, t_pos *mapsize, t_pos pudpos)
{
	int puddles;

	puddles = 0;
	// if water leak goes to the edge
	if (!pudpos.y || !pudpos.x || pudpos.y == mapsize->y - 1 || pudpos.x == mapsize->x - 1)
		return (-1);
	printf("found at (%d, %d)\n", pudpos.x, pudpos.y);
	if (set_new_puddle(nmap, pudpos.x, pudpos.y - 1, &puddles) < 0)
		return (-1);
	if (set_new_puddle(nmap, pudpos.x + 1, pudpos.y, &puddles) < 0)
		return (-1);
	if (set_new_puddle(nmap, pudpos.x, pudpos.y + 1, &puddles) < 0)
		return (-1);
	if (set_new_puddle(nmap, pudpos.x - 1, pudpos.y, &puddles) < 0)
		return (-1);
	nmap[pudpos.y][pudpos.x] = 'x';
	return (puddles);
}

int			waterdrop(int **map, t_pos *mapsize, t_pos *ppl)
{
	int **cmap;
	int **nmap;
	int puddles;
	t_pos pudpos;

	int err;

	cmap = dup_array(map, mapsize->x, mapsize->y);
	nmap = dup_array(map, mapsize->x, mapsize->y);
	puddles = 1;
	err = 0;
	ft_aff_map(cmap, mapsize, ppl);

	cmap[ppl->y][ppl->x] = '+';

	pudpos.x = 0;
	pudpos.y = 0;
	while (puddles)
	{
		puddles = 0;
		pudpos.y = 0;
		while (pudpos.y < mapsize->y)
		{
			pudpos.x = 0;
			while (pudpos.x < mapsize->x)
			{
				if (cmap[pudpos.y][pudpos.x] == '+')
				{
					err = water_puddle(nmap, mapsize, pudpos);
					if (err < 0)
					{
						remove_2d_array(cmap, mapsize->y);
						remove_2d_array(nmap, mapsize->y);
						return (err);
					}
					puddles += err;
				}
				pudpos.x++;
			}
			pudpos.y++;
		}
		remove_2d_array(cmap, mapsize->y);
		cmap = dup_array(nmap, mapsize->x, mapsize->y);
		ft_aff_map(nmap, mapsize, ppl);
	}
	remove_2d_array(cmap, mapsize->y);
	remove_2d_array(nmap, mapsize->y);
	return (puddles);
}
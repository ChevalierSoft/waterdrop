#include "waterdrop.h"
//#include <windows.h>

int	set_new_puddle(int **nmap, int px, int py, position_t mapsize, int *puddles)
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

int	water_puddle(int **nmap, position_t mapsize, position_t pudpos)
{
	int puddles;

	puddles = 0;
	// if water leak goes to the edge
	if (!pudpos.y || !pudpos.x || pudpos.y == mapsize.y - 1 || pudpos.x == mapsize.x - 1)
		return (-1);
	printf("found at (%d, %d)\n", pudpos.x, pudpos.y);
	if (set_new_puddle(nmap, pudpos.x, pudpos.y - 1, mapsize, &puddles) < 0)
		return (-1);
	if (set_new_puddle(nmap, pudpos.x + 1, pudpos.y, mapsize, &puddles) < 0)
		return (-1);
	if (set_new_puddle(nmap, pudpos.x, pudpos.y + 1, mapsize, &puddles) < 0)
		return (-1);
	if (set_new_puddle(nmap, pudpos.x - 1, pudpos.y, mapsize, &puddles) < 0)
		return (-1);
	nmap[pudpos.y][pudpos.x] = 'x';
	return (puddles);
}

int waterdrop(int **map, position_t mapsize, position_t *ppl)
{
	int **cmap;
	int **nmap;
	int puddles;
	position_t pudpos;
	int wx;
	int wy;
	int err;

	cmap = dup_array(map, mapsize.x, mapsize.y);
	nmap = dup_array(map, mapsize.x, mapsize.y);
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
		while (pudpos.y < mapsize.y)
		{
			pudpos.x = 0;
			while (pudpos.x < mapsize.x)
			{
				if (cmap[pudpos.y][pudpos.x] == '+')
				{
					err = water_puddle(nmap, mapsize, pudpos);
					if (err < 0)
						return (err);
					puddles += err;
				}
				pudpos.x++;
			}
			pudpos.y++;
		}
		del_2Darray(cmap, mapsize.y);
		cmap = dup_array(nmap, mapsize.x, mapsize.y);
		ft_aff_map(nmap, mapsize, ppl);
	}
	del_2Darray(cmap, mapsize.y);
	del_2Darray(nmap, mapsize.y);
	return (puddles);
}

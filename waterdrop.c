#include "waterdrop.h"

// le split du water drop devrait se faire uniquement en N S E W, pas en diagonale

int	water_puddle(int **wmap, position_t mapsize, position_t pudpos)
{
	//
	if (!pudpos.y || !pudpos.x || pudpos.y == mapsize.y || pudpos.x == mapsize.x)
		return (-1);

	// if ()
}

int waterdrop(int **map, position_t mapsize, position_t *ppl)
{
	int **wmap;
	int puddles;
	position_t pudpos;
	int wx;
	int wy;

	wmap = dup_array(map, mapsize.x, mapsize.y);
	puddles = 1;

	ft_aff_map(wmap, mapsize, ppl);

	wmap[ppl->y][ppl->x] = '+';

	pudpos.x = 0;
	pudpos.y = 0;
	// while (puddle)
	// {
		pudpos.y = 0;
		while (pudpos.y < mapsize.y)
		{
			pudpos.x = 0;
			while (pudpos.x < mapsize.x)
			{
				if (wmap[pudpos.y][pudpos.x] == '+')
				{
					if ((puddles = water_puddle(wmap, mapsize, pudpos)) < 0)
						return (puddles);
				}
				pudpos.x++;
			}
			pudpos.y++;
		}
	// }

	del_2Darray(wmap, mapsize.y);
	return (puddles);
}
#include "waterdrop.h"

// le split du water drop devrait se faire uniquement en N S E W, pas en diagonale

int	ft_aff_waterdrop(int **map, int mapX, int mapY, position_t *ppl)
{
	int i;
	int j;

	printf("\n");
	j = 0;
	while (j < mapY)
	{
		i = 0;
		while (i < mapX)
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
					printf(GRN "%d " RST, map[j][i++]);
				else if (map[j][i] == '+')
					printf(BLU "%d " RST, map[j][i++]);
				else
					printf(YEL "%d " RST, map[j][i++]);
			}
		}
		printf("\n");
		j++;
	}
	printf("\n======== \n");
}

int	water_puddle(int **wmap, int my, int mx, position_t pudpos)
{
	//
	if (!pudpos.y || !pudpos.x || pudpos.y == my || pudpos.x == mx);
}

int waterdrop(int **map, int mx, int my, position_t *ppl)
{
	int **wmap;
	int puddles;
	position_t pudpos;
	int wx;
	int wy;

	wmap = dup_array(map, mx, my);
	puddles = 1;

	ft_aff_waterdrop(wmap, mx, my, ppl);

	wmap[ppl->y][ppl->x] = '+';

	pudpos.x = 0;
	pudpos.y = 0;
	// while (puddle)
	// {
		pudpos.y = 0;
		while (pudpos.y < my)
		{
			pudpos.x = 0;
			while (pudpos.x < my)
			{
				if (wmap[pudpos.y][pudpos.x] == '+')
				{
					puddles = water_puddle(wmap, mx, my, pudpos);
				}
				pudpos.x++;
			}
			pudpos.y++;
		}
	// }

	del_2Darray(wmap, my);
}
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
	zero(map, mx, my, ' ');
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
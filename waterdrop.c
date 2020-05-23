#include "waterdrop.h"

int waterdrop(int **map, int mx, int my, position_t *ppl)
{
	int **wmap;
	int puddle;
	
	wmap = dup_array(map, mx, my);
	puddle = 0;

	del_2Darray(wmap, my);
}
#ifndef WATERDROP_H
# define WATERDROP_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include "color.h"

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

	void			help();
	void			printr(char *s);
	void			print(char *s);
	int				ft_strlen(char *s);

	int				**init_2Darray(int mx, int my);
	void			del_2Darray(int **map, int my);
	int 			**dup_array(int **map, int mx, int my);
	int				ft_aff_map(int **map, position_t mapsize, position_t *ppl);

	int 			waterdrop(int **map, position_t mapsize, position_t *ppl);

#endif
#ifndef WATERDROP_H
# define WATERDROP_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include "color.h"
# include "libft.h"

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

	typedef struct	map_s
	{
		int sx;
		int sy;
		int **data;
	}				map_t;

	typedef struct	meta_s
	{
		int		WW;
		int		WH;
		char	*strR;
		char	*pathN;
		char	*pathS;
		char	*pathE;
		char	*pathW;
		char	*pathSP;
		char	*pathF;
		char	*pathR;
	}				meta_t;

	// debug.c
	void			help();
	void			printr(char *s);
	void			print(char *s);
	int				ft_aff_file(char *name);

	// gnl
	int				get_next_line(int fd, char **line);

	// get_infos.c
	int 			get_infos(meta_t *meta, int fd, int *straff, position_t *ms, position_t *ppl);


	// array_tools.c
	int				**init_2Darray(int mx, int my);
	void			del_2Darray(int **map, int my);
	int 			**dup_array(int **map, int mx, int my);

	//meta.c
	void			aff_meta(meta_t *meta);
	meta_t			*meta_init(void);
	void			remove_meta(meta_t **m);

	// verif_cub.c
	void			ft_aff_map(int **map, position_t mapsize, position_t *ppl);

	// waterdrop.c
	int 			waterdrop(int **map, position_t mapsize, position_t *ppl);

#endif

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

	// debug.c
	void			help();
	void			printr(char *s);
	void			print(char *s);
	int				ft_strlen(char *s);
	// soon from libft
	char			*ft_strncpy(char *dst, char *src, size_t len);
	void			*ft_memcpy(void *dst, void *src, size_t n);
	char			*ft_strdup(char *s1);
	void			*ft_memset(void *b, int c, size_t len);
	char			*ft_strjoin(char *s1, char *s2);

	// gnl
	int				get_next_line(int fd, char **line);

	// get_infos.c
	int				get_infos(char *name);

	// verif_cub.c
	int				**init_2Darray(int mx, int my);
	void			del_2Darray(int **map, int my);
	int 			**dup_array(int **map, int mx, int my);
	void			ft_aff_map(int **map, position_t mapsize, position_t *ppl);

	// waterdrop.c
	int 			waterdrop(int **map, position_t mapsize, position_t *ppl);

#endif

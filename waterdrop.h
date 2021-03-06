/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waterdrop.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 06:57:11 by dait-atm          #+#    #+#             */
/*   Updated: 2020/07/11 06:57:23 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WATERDROP_H
# define WATERDROP_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include "color.h"
# include "libft/libft.h"

#define MAP_FOUND 89
#define ERROR_INFO -4
#define ERROR_NO_SPAWN -11
#define ERROR_DOUBLE_SPAWN -22
#define ERROR_RESOLUTION -480
#define ERROR_WRONG_CHAR -44
#define ERROR_DAMAGED_MEMORY -404
#define GNL_EOF 0

typedef struct	s_pos
{
	int x;
	int y;
	int o;
}				t_pos;

typedef struct	s_map
{
	int sx;
	int sy;
	int **data;
}				t_map;

typedef struct	s_meta
{
	int		ww;
	int		wh;
	char	*str_r;
	char	*path_n;
	char	*path_s;
	char	*path_e;
	char	*path_w;
	char	*path_sp;
	char	*path_f;
	char	*path_c;
}				t_meta;

typedef struct	s_intel
{
	int		**map;
	char	*filename;	// rm
	t_meta	*meta;		//	--> g->textures
	t_pos	*ppl;		//	--> g->player->px/py
	t_pos	*map_size;	//	--> g->map->sx/sy
	int		map_offset;	// rm
	int		fd;			// rm
}				t_intel;

// debug.c
void			help();
void			alert(void);
void			printr(char *s);
void			print(char *s);
int				ft_aff_file(char *name);
void			aff_meta(t_meta *meta);
void			ft_aff_map(int **map, t_pos *mapsize, t_pos *ppl);

// quit.c
void			flush_quit(char *msg, t_intel **it, int code);

// reddit.c
int				reddit(t_intel *it, char *l);

// get_infos.c
int				set_r(t_meta *meta);
int				get_infos(t_intel *it);

// array_tools.c
int				**init_2d_array(int mx, int my);
void			remove_2d_array(int ***map, int my);
int				**dup_array(int **map, int mx, int my);

// meta.c
t_meta			*meta_init(void);
void			remove_meta(t_meta **m);

// intel.c
t_intel			*create_intel(void);
void			remove_intel(t_intel **it);

// main.c
void			flush_quit(char *msg, t_intel **it, int code);

// waterdrop.c
int				waterdrop(int **map, t_pos *mapsize, t_pos *ppl);

#endif

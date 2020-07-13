#include "waterdrop.h"

#define MAP_FOUND 89
#define ERROR_INFO -4
#define ERROR_DOUBLE_SPAWN -22
#define ERROR_RESOLUTION -480
#define ERROR_WRONG_CHAR -44

static int	set_r(t_meta *meta)
{
	int i;

	i = 0;
	if ((meta->ww = ft_atoi(meta->str_r)) <= 3)
	{
		print("Error\nWrong width resolution in .cub file\n");
		return (-1);
	}
	while (meta->str_r[i] != ' ')
		i++;
	i++;
	if ((meta->wh = atoi(meta->str_r + i)) <= 3)
	{
		print("Error\nWrong high resolution in .cub file\n");
		return (-2);
	}
	return (0);
}

static void	inc_map_offset(char *l, int *map_offset, int d)
{
	// int len;

	// len = ft_strlen(l);
	(*map_offset) += ft_strlen(l) + d + 1; // endl = 1
}

static int	dup4meta(char **s, char *l, int *map_offset, int d)
{
	inc_map_offset(l, map_offset, d);
	if (!((*s) = ft_strdup(l)))
	{
		print("Error\nNot enough RAM for t_meta strings\n");
		return (-1);
	}
	return (0);
}

static int	reddit(t_meta *meta, char *l, int *map_offset)
{
	int err;

	err = 0;
	if (!l || !meta)
	{
		print("Error\nDamaged memory\n");
		return (-2);
	}
	else if (!l[0])	// ligne vide
		(*map_offset)++;	// return (0);
	else if (!ft_strncmp(l, "R ", 2))
	{
		err = dup4meta(&meta->str_r, l + 2, map_offset, 2);
		if ((err = set_r(meta)) < 0)
			return (err);
	}
	else if (!ft_strncmp(l, "NO ", 3))
		err = dup4meta(&meta->path_n, l + 3, map_offset, 3);
	else if (!ft_strncmp(l, "SO ", 3))
		err = dup4meta(&meta->path_s, l + 3, map_offset, 3);
	else if (!ft_strncmp(l, "EA ", 3))
		err = dup4meta(&meta->path_e, l + 3, map_offset, 3);
	else if (!ft_strncmp(l, "WE ", 3))
		err = dup4meta(&meta->path_w, l + 3, map_offset, 3);
	else if (!ft_strncmp(l, "S ", 2))
		err = dup4meta(&meta->path_sp, l + 2, map_offset, 2);
	else if (!ft_strncmp(l, "F ", 2))
		err = dup4meta(&meta->path_f, l + 2, map_offset, 2);
	else if (!ft_strncmp(l, "C ", 2))
		err = dup4meta(&meta->path_c, l + 2, map_offset, 2);
	else if (ft_memchr(" 012NSEW", *l, 8))
	{
		// printf("c'est la map : %s\n", l);
		if (!(meta->path_n && meta->path_s && meta->path_e && meta->path_w
			&& meta->path_sp && meta->path_f && meta->path_c))
		{
			print("Error\nlake of intel before the map in .cub file\n");
			return (ERROR_INFO);
		}
		return(MAP_FOUND);
	}
	else
	{
		print("Error\nWrong line in .cub file\n");
		return (-3);
	}
	return (err);
}

int		ledgit_square(char c, t_pos *ppl, int vx, int mapY)
{
	if (c == '0' || c == '1' || c == '2' || c == ' ')
		return (1);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (ppl->x != -1 || ppl->y != -1)
			return (ERROR_DOUBLE_SPAWN);
		ppl->x = vx;
		ppl->y = mapY - 1;
		ppl->o = c;
		return (1);
	}
	else
		return (-1);
}

int		ft_get_mapXY(char *l, t_pos *mapsize, t_pos *ppl)
{
	char	res;
	int		vx;

	vx = 0;
	while (*l)
	{
		if (ledgit_square(*l, ppl, vx, mapsize->y) > 0)
			vx++;
		else
		{
			free(l);
			l = NULL;
			print("Error\nwrong character for the map in .cub file\n");
			// write(1, "Error\ncaractere inaproprié : %c\n", *l);
			return (ERROR_WRONG_CHAR);
		}
		l++;
	}
	if (mapsize->x < vx)
		mapsize->x = vx;
	mapsize->y++;
	return (0);
}

int 	get_infos(t_meta *meta, int fd, int *map_offset, t_pos *ms, t_pos *ppl)
{
	char *l = NULL;
	int err;
	int gnl;
	t_meta map;

	err = 0;
	while (err >= 0 && (gnl = get_next_line(fd, &l)) > 0)
	{
		if ((err = reddit(meta, l, map_offset)) == MAP_FOUND)
			break ;
		free(l);
	}
	// printf("map_offset : %d\n", *map_offset);
	if (err == MAP_FOUND)
	{
		ms->y++;
		if ((err = ft_get_mapXY(l, ms, ppl)) >= 0)
			free(l);
		while (err >= 0 && (gnl = get_next_line(fd, &l)) > 0)
		{
			err = ft_get_mapXY(l, ms, ppl);
			free(l);
		}
		free(l);
	 	printf("mapsize : (%d, %d)\n", ms->x, ms->y);
	 	printf("ppl->x = %d : ppl->y = %d : ppl->o = %c\n", ppl->x, ppl->y, ppl->o);
	}
	// aff_meta(meta);
	return (err);
}

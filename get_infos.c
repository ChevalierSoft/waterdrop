#include "waterdrop.h"

#define MAP_FOUND 89
#define ERROR_INFO -4
#define ERROR_NO_SPAWN -11
#define ERROR_DOUBLE_SPAWN -22
#define ERROR_RESOLUTION -480
#define ERROR_WRONG_CHAR -44
#define ERROR_DAMAGED_MEMORY -404
#define GNL_EOF 0

/*
** in set_r()
** need to test meta->ww and meta->wh < mlx_get_screen_size
*/

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
		print("Error\nWrong height resolution in .cub file\n");
		return (-2);
	}
	return (0);
}

static int	dup4meta(char **s, char *l, int *map_offset, int d)
{
	(*map_offset) += ft_strlen(l) + d + 1;
	if (!((*s) = ft_strdup(l)))
	{
		print("Error\nNot enough RAM for t_meta strings\n");
		return (-1);
	}
	return (0);
}

static int	reddit(t_intel *it, char *l)
{
	int err;

	err = 0;
	if (!l || !it->meta)
	{
		print("Error\nDamaged memory\n");
		return (ERROR_DAMAGED_MEMORY);
	}
	else if (!l[0])	// ligne vide
		it->map_offset++;	// return (0);
	else if (!ft_strncmp(l, "R ", 2))
	{
		err = dup4meta(&it->meta->str_r, l + 2, &it->map_offset, 2);
		if ((err = set_r(it->meta)) < 0)
			return (err);
	}
	else if (!ft_strncmp(l, "NO ", 3))
		err = dup4meta(&it->meta->path_n, l + 3, &it->map_offset, 3);
	else if (!ft_strncmp(l, "SO ", 3))
		err = dup4meta(&it->meta->path_s, l + 3, &it->map_offset, 3);
	else if (!ft_strncmp(l, "EA ", 3))
		err = dup4meta(&it->meta->path_e, l + 3, &it->map_offset, 3);
	else if (!ft_strncmp(l, "WE ", 3))
		err = dup4meta(&it->meta->path_w, l + 3, &it->map_offset, 3);
	else if (!ft_strncmp(l, "S ", 2))
		err = dup4meta(&it->meta->path_sp, l + 2, &it->map_offset, 2);
	else if (!ft_strncmp(l, "F ", 2))
		err = dup4meta(&it->meta->path_f, l + 2, &it->map_offset, 2);
	else if (!ft_strncmp(l, "C ", 2))
		err = dup4meta(&it->meta->path_c, l + 2, &it->map_offset, 2);
	else if (ft_memchr(" 012NSEW", *l, 8))
	{
		if (!(it->meta->str_r && it->meta->path_n && it->meta->path_s && it->meta->path_e
			&& it->meta->path_w && it->meta->path_sp && it->meta->path_f && it->meta->path_c))
		{
			print("Error\nLake of intel before the map in .cub file\n");
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

static int	ledgit_square(char c, t_pos *ppl, int vx, int mapY)
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

static int	ft_get_mapXY(char *l, t_pos *mapsize, t_pos *ppl)
{
	int		vx;

	vx = 0;
	while (*l)
	{
		if (ledgit_square(*l, ppl, vx, mapsize->y) > 0)
			vx++;
		else
		{
			print("Error\nWrong character for the map in .cub file\n");
			return (ERROR_WRONG_CHAR);
		}
		l++;
	}
	if (mapsize->x < vx)
		mapsize->x = vx;
	mapsize->y++;
	return (0);
}

int			get_infos(t_intel *it)
{
	char *l = NULL;
	int err;
	int gnl;

	err = 0;
	while (err >= 0 && (gnl = get_next_line(it->fd, &l)) > 0)
	{
		if ((err = reddit(it, l)) == MAP_FOUND)
			break ;
		free(l);
	}
	if (err == MAP_FOUND)
	{
		(it->map_size->y) = (it->map_size->y) + 1;
		err = ft_get_mapXY(l, it->map_size, it->ppl);
		free(l);
		while (err >= 0 && (gnl = get_next_line(it->fd, &l)) > 0)
		{
			err = ft_get_mapXY(l, it->map_size, it->ppl);
			free(l);
		}
		if (gnl == GNL_EOF)
			free(l);
		if (it->ppl->x == -1)
		{
			err = ERROR_NO_SPAWN;
			print("Error\nNo spawn in .cub file\n");
		}
	}
	return (err);
}

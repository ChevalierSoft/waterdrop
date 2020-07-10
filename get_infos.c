#include "waterdrop.h"

#define MAP_FOUND 89
#define ERROR_INFO -4
#define DOUBLE_SPAWN -22

static int	set_R(meta_t *meta)
{
	int i;

	i = 0;
	if ((meta->WW = atoi(meta->strR)) <= 0)
	{
		printf("Error\nWrong resolution in .cub file");
		return (-1);
	}
	while (meta->strR[i] != ' ')
		i++;
	i++;
	meta->WH = atoi(meta->strR + i);

	return (0);
}

static void	inc_straff(char *l, int *straff, int d)
{
	int len;

	len = ft_strlen(l);
	(*straff) += len + d + 1; // endl = 1
}

static int	dup4meta(char **s, char *l, int *straff, int d)
{
	inc_straff(l, straff, d);
	if (!(*s = ft_strdup(l)))
	{
		printf("Error\nNot enough RAM for meta_t strings\n");
		return (-1);
	}
	return (0);
}

static int	readit(meta_t *meta, char *l, int *straff)
{
	int err;

	err = 0;
	if (!l || !meta)
		return (-2);
	else if (!l[0])	// ligne vide
	{
		(*straff)++;
		return (0);
	}
	else if (!ft_strncmp(l, "R ", 2))
	{
		err = dup4meta(&meta->strR, l + 2, straff, 2);
		if ((err = set_R(meta)) < 0)
			return (err);
	}
	else if (!ft_strncmp(l, "NO ", 3))
		err = dup4meta(&meta->pathN, l + 3, straff, 3);
	else if (!ft_strncmp(l, "SO ", 3))
		err = dup4meta(&meta->pathS, l + 3, straff, 3);
	else if (!ft_strncmp(l, "EA ", 3))
		err = dup4meta(&meta->pathE, l + 3, straff, 3);
	else if (!ft_strncmp(l, "WE ", 3))
		err = dup4meta(&meta->pathW, l + 3, straff, 3);
	else if (!ft_strncmp(l, "S ", 2))
		err = dup4meta(&meta->pathSP, l + 2, straff, 2);
	else if (!ft_strncmp(l, "F ", 2))
		err = dup4meta(&meta->pathF, l + 2, straff, 2);
	else if (!ft_strncmp(l, "C ", 2))
		err = dup4meta(&meta->pathR, l + 2, straff, 2);
	else if (ft_memchr(" 012NSEW", *l, 8))
	{
		printf("c'est la map : %s\n", l);
		if (!(meta->pathN && meta->pathS && meta->pathE && meta->pathW
			&& meta->pathSP && meta->pathF && meta->pathR))
		{
			printf("Error\nlake of intel before the map in .cub file\n");
			return (ERROR_INFO);
		}
		return(MAP_FOUND);
	}
	else
	{
		printf("Error\nWrong line in .cub file\nstraff : %d", *straff);
		return (-3);
	}
	return (err);
}

int	ledgit_square(char c, position_t *ppl, int vx, int mapY)
{
	if (c == '0' || c == '1' || c == '2' || c == ' ')
		return (1);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (ppl->x != -1 || ppl->y != -1)
			return (DOUBLE_SPAWN);
		ppl->x = vx;
		ppl->y = mapY - 1;
		ppl->o = c;
		return (1);
	}
	else
		return (-1);
}

int		ft_get_mapXY(char *l, position_t *mapsize, position_t *ppl)
{
	char res;
	int vx;

	vx = 0;
	while (*l)
	{
		if (ledgit_square(*l, ppl, vx, mapsize->y) > 0)
			vx++;
		else
		{
			printf("Error\ncaractere inaproprié : %c\n", *l);
			return (-2);
		}
		l++;
	}
	if (mapsize->x < vx)
		mapsize->x = vx;
	mapsize->y++;
	return (0);
}

int 	get_infos(meta_t *meta, int fd, int *straff, position_t *ms, position_t *ppl)
{
	char *l = NULL;
	int err;
	int gnl;
	map_t map;

	err = 0;
	while (err >= 0 && (gnl = get_next_line(fd, &l)) > 0)
	{
		if ((err = readit(meta, l, straff)) == MAP_FOUND)
		{
			break ;
		}
		//printf(">%s<\n", l);
		free(l);
	}
	printf("straff : %d\n", *straff);
	if (err == MAP_FOUND)
	{
		ms->y++;
		ft_get_mapXY(l, ms, ppl);
		while (err >= 0 && (gnl = get_next_line(fd, &l)) > 0)
		{
			err = ft_get_mapXY(l, ms, ppl);
			free(l);
		}
	 	printf("mapsize : (%d, %d)\n", ms->x, ms->y);
	 	printf("ppl->x = %d : ppl->y = %d : ppl->o = %c\n", ppl->x, ppl->y, ppl->o);
	}
	// printf("		 : %d\n", gnl);
	aff_meta(meta);	
	return (err);
}

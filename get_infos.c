#include "waterdrop.h"

#define MAP_FOUND 89

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

static int	dup4meta(char **d, char *l)
{
	if (!(*d = ft_strdup(l)))
	{
		printf("Error\nNot enough RAM for meta_t strings\n");
		return (-1);
	}

	return (0);
}

static int	readit(meta_t *meta, char *l, int line)
{
	int err;

	err = 0;
	if (!l || !meta)
		return (-2);
	else if (!l[0])	// ligne vide
		return (0);
	else if (!ft_strncmp(l, "R ", 2))
	{
		err = dup4meta(&meta->strR, l + 2);
		if ((err = set_R(meta)) < 0)
			return (err);
	}
	else if (!ft_strncmp(l, "NO ", 3))
		err = dup4meta(&meta->pathN, l + 3);
	else if (!ft_strncmp(l, "SO ", 3))
		err = dup4meta(&meta->pathS, l + 3);
	else if (!ft_strncmp(l, "EA ", 3))
		err = dup4meta(&meta->pathE, l + 3);
	else if (!ft_strncmp(l, "WE ", 3))
		err = dup4meta(&meta->pathW, l + 3);
	else if (!ft_strncmp(l, "S ", 2))
		err = dup4meta(&meta->pathSP, l + 2);
	else if (!ft_strncmp(l, "F ", 2))
		err = dup4meta(&meta->pathF, l + 2);
	else if (!ft_strncmp(l, "C ", 2))
		err = dup4meta(&meta->pathR, l + 2);
	else if (ft_memchr(" 012NSEW", *l, 8))
	{
		printf("c'est la map : %s\n", l);
		if (!(meta->pathN && meta->pathS && meta->pathE && meta->pathW
			&& meta->pathSP && meta->pathF && meta->pathR))
		{
			printf("Error\nlake of intel before the map in .cub file\n");
			return (-4);
		}
		return(MAP_FOUND);
	}
	else
	{
		printf("Error\nWrong line in .cub file\nline %d", line);
		return (-3);
	}
	return (err);
}

int get_infos(meta_t *meta, int fd, int *line)
{
	char *l = NULL;
	int err;
	int gnl;

	map_t map;

	err = 0;
	while (err >= 0 && (gnl = get_next_line(fd, &l)) > 0)
	{
		err = readit(meta, l, *line);
		//printf(">%s<\n", l);
		free(l);
		(*line)++;
	}
	
	// if (!err)
	// {
	// 	// printf(">%s<\n", l);
	// 	printf("reached the end ++\n");
	// 	err = readit(meta, l, *line);
	// 	free(l);
	// }

	printf("gnl : %d\n", gnl);
	aff_meta(meta);
	
	return (0);
}

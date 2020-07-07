#include "waterdrop.h"

void	aff_meta(meta_t *meta)
{
	printf("R  : %s\n", meta->strR);
	printf("NO : %s\n", meta->pathN);
	printf("SO : %s\n", meta->pathS);
	printf("EA : %s\n", meta->pathE);
	printf("WE : %s\n", meta->pathW);
	printf("SP : %s\n", meta->pathSP);
	printf("F  : %s\n", meta->pathF);
	printf("C  : %s\n", meta->pathR);
}

int	set_R(meta_t *meta, char *l)
{
	return (0);
}

int	readit(meta_t *meta, char *l)
{
	//if (!l[0])
	//	return (0);
	if (!ft_strncmp(l, "R ", 2))
		//set_line(meta->strR, l + 2);
		meta->strR = ft_strdup(l + 2);

	else if (!ft_strncmp(l, "NO ", 3))
		meta->pathN = ft_strdup(l + 3);
	else if (!ft_strncmp(l, "SO ", 3))
		meta->pathS = ft_strdup(l + 3);

	else if (!ft_strncmp(l, "EA ", 3))
		meta->pathE = ft_strdup(l + 3);
	else if (!ft_strncmp(l, "WE ", 3))
		meta->pathW = ft_strdup(l + 3);

	else if (!ft_strncmp(l, "S ", 2))
		meta->pathSP = ft_strdup(l + 2);
	else if (!ft_strncmp(l, "F ", 2))
		meta->pathF = ft_strdup(l + 2);
	else if (!ft_strncmp(l, "C ", 2))
		meta->pathR = ft_strdup(l + 2);
	//else
	//	return (-1);
	return (0);
}

int get_infos(meta_t *meta, char *name)
{
	int fd;
	char *l = NULL;
	int err;

	if ((fd = open(name, O_RDONLY)) < 0)
	{
		print("wrong .cub file path\n");
		return (-1);
	}
	err = 0;
	while (err >= 0 && get_next_line(fd, &l))
	{
		err = readit(meta, l);
		printf(">%s<\n", l);
		//free(l);
	}
	printf(">%s<\n", l);
	free(l);
	aff_meta(meta);
	return (0);
}

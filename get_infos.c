#include "waterdrop.h"


int		get_next_line(int fd, char **line);


int		get_infos(char *name)
{
	int fd;
	char *l;

	if ((fd = open(name, O_RDONLY)) < 0)
	{
		printf("wrong path to .cub file\n");
		return (-1);
	}

	while(get_next_line(0, &l))
	{
		print(l);
		write(1, "\n", 1);
		free(l);
	}
	print(l);
	write(1, "\n", 1);
	free(l);
	close(fd);
	return (0);
}
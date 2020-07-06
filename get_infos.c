#include "waterdrop.h"

int get_infos(char *name)
{
	int fd;
	char *l = NULL;

	if ((fd = open(name, O_RDONLY)) < 0)
	{
		print("wrong .cub file path\n");
		return (-1);
	}
	// fd = 0;
	while (get_next_line(fd, &l))
	{
		printf(">%s<\n", l);
		free(l);
	}
	printf(">%s<\n", l);
	free(l);
	return (0);
}

#include "waterdrop.h"

int get_infos(char *name)
{
    int fd;
    char *l;

    if ((fd = open(name, O_RDONLY)) < 0)
	{
		print("wrong .cub file path\n");
		return (-1);
    }
	while (get_next_line(fd, &l))
    {
		print(">");
        print(l);
		print("\n");
        free(l);
    }
    printf(">%s\n", l);
    free(l);
    return (0);
}

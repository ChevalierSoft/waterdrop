#include "waterdrop.h"

void	print(char *s)
{
	
	write(1, s, ft_strlen(s));
}

void	printr(char *s)
{
	print(MAG);
	print(s);
	print(RST);
}

void	help(void)
{
	printr("help\n");
}

#include "waterdrop.h"

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i++])
		;
	return (i);
}

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
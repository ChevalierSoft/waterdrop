#include "waterdrop.h"

void	flush_quit(char *msg, t_intel **it, int code)
{
	print(msg);
	remove_intel(it);
	exit(code);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 02:01:48 by dait-atm          #+#    #+#             */
/*   Updated: 2020/02/18 16:42:33 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 64
#endif

#define FD_MAX 75000
#define ALERTE -1

inline void		*ft_memset(void *b, int c, size_t len)
{
	void *beg;

	beg = b;
	while (len--)
	{
		*((char *)b) = (unsigned char)c;
		b++;
	}
	return (beg);
}

static int		ret_a_plus(int *a, int r)
{
	(*a)++;
	return (r);
}

static int		ret_a_zero(int *a, int r)
{
	(*a) = 0;
	return (r);
}

static int		bosg(int *a, char *buff, char **line, int res)
{
	char mas[2];
	char *tmp;

	mas[1] = '\0';
	while (*a < res)
	{
		tmp = (*line);
		if (buff[*a] == '\n')
			return (ret_a_plus(a, 1));
		else
		{
			mas[0] = buff[(*a)++];
			if (!((*line) = ft_strjoin(tmp, mas)))
			{
				free(tmp);
				return (ALERTE);
			}
			free(tmp);
		}
	}
	if (res != BUFFER_SIZE)
		return (ret_a_zero(a, 0));
	return (RAS);
}

extern int		get_next_line(int fd, char **line)
{
	static long	res[OPEN_MAX];
	static char	buff[OPEN_MAX][BUFFER_SIZE];
	static int	a[OPEN_MAX];
	int			is_ok;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1 || read(fd, buff[fd], 0) < 0)
		return (-1);
	(*line) = ft_strdup("");
	if (a[fd] > 0 && a[fd] < BUFFER_SIZE && buff[fd][a[fd]])
	{
		if (res[fd] < BUFFER_SIZE)
			return (bosg(&(a[fd]), buff[fd], line, res[fd]));
		if ((is_ok = bosg(&(a[fd]), buff[fd], line, res[fd])) != RAS)
			return (is_ok);
	}
	while ((res[fd] = read(fd, buff[fd], BUFFER_SIZE)))
	{
		a[fd] = 0;
		if (res[fd] < BUFFER_SIZE)
			return (bosg(&(a[fd]), buff[fd], (line), res[fd]));
		else if ((is_ok = bosg(&(a[fd]), buff[fd], line, BUFFER_SIZE) != RAS))
			return (is_ok);
		ft_memset(buff, 0, BUFFER_SIZE);
	}
	return (0);
}

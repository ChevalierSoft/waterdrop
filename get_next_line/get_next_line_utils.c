/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 13:13:55 by dait-atm          #+#    #+#             */
/*   Updated: 2020/07/07 19:07:11 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 64
#endif

#define RAS 619
#define FD_MAX 75000
#define ALERTE -1

inline size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

inline char		*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;

	i = 0;
	while (len)
	{
		if (!src[i])
		{
			while (len--)
				dst[i++] = '\0';
			break ;
		}
		dst[i] = src[i];
		i++;
		len--;
	}
	return (dst);
}

inline void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}

inline char		*ft_strdup(const char *s1)
{
	char	*r;
	size_t	sz;

	sz = ft_strlen(s1) + 1;
	if (!(r = malloc(sz)))
		return (0);
	return (ft_memcpy(r, s1, sz));
}

inline char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (0);
	s2len = ft_strlen(s2);
	s1len = ft_strlen(s1);
	if (!(s3 = (malloc(sizeof(char) * (s1len + s2len + 1)))))
		return (0);
	ft_strncpy(s3, s1, s1len);
	ft_strncpy(s3 + s1len, s2, s2len);
	s3[s1len + s2len] = '\0';
	return (s3);
}

/////////////////////////////////////////////

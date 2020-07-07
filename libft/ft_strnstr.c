/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 15:40:30 by dait-atm          #+#    #+#             */
/*   Updated: 2019/11/18 14:59:00 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_strchr_2(const char *s, char c)
{
	unsigned int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		s++;
	}
	return (-1);
}

char			*ft_strnstr(const char *src, const char *needle, size_t len)
{
	size_t			i;
	size_t			ln;

	i = 0;
	if (!*needle)
		return ((char *)src);
	if (!needle)
		return (0);
	else if (ft_strchr_2(src, needle[0]) < 0)
		return (0);
	ln = ft_strlen(needle);
	while (i < len && src[i])
	{
		if (!ft_strncmp((char *)(src + i), (char *)needle, ln) && len - i >= ln)
			return ((char *)src + i);
		i++;
	}
	return (0);
}

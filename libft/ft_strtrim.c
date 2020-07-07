/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 18:17:25 by dait-atm          #+#    #+#             */
/*   Updated: 2019/11/20 17:56:36 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_from_base(char c, const char *set)
{
	while (*set)
	{
		if (*set++ == c)
			return (1);
	}
	return (0);
}

static size_t	count_setlen_lr(const char *s, const char *set, int sens)
{
	size_t	i;

	if (sens == -1)
		i = ft_strlen(s) - 1;
	else
		i = 0;
	while (s[i])
	{
		if (!ft_is_from_base(s[i], set))
			return (i);
		i += sens;
	}
	return (i);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	size_t	beg;
	size_t	size;
	char	*s2;

	if (!s1)
		return (0);
	if (!set || s1[0] == 0)
		return (ft_strdup(""));
	beg = count_setlen_lr(s1, set, 1);
	if (beg == ft_strlen(s1))
		return (ft_strdup(""));
	size = 1 + count_setlen_lr(s1, set, -1) - beg;
	if (!(s2 = malloc(sizeof(char) * size + 1)))
		return (0);
	ft_memcpy(s2, s1 + beg, size);
	s2[size] = 0;
	return (s2);
}

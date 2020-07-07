/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:54:33 by dait-atm          #+#    #+#             */
/*   Updated: 2019/11/19 23:41:38 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*ft_size_w(const char *str, char c, size_t isset)
{
	if (isset)
		while (*str != 0 && *str == c)
			str++;
	else
		while (*str != 0 && *str != c)
			str++;
	return (str);
}

static size_t		ft_count_words(const char *str, char c)
{
	size_t i;

	i = 0;
	while (*str != 0)
	{
		str = ft_size_w(str, c, 1);
		if (*str != 0)
		{
			i++;
			str = ft_size_w(str, c, 0);
		}
	}
	return (i);
}

static char			**ft_tabledel(char **ret, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
		free(ret[i]);
	free(ret);
	return (NULL);
}

char				**ft_split(char const *str, char c)
{
	char		**lt;
	const char	*next;
	size_t		i;

	if (!str)
		return (NULL);
	lt = malloc(sizeof(char *) * (ft_count_words(str, c) + 1));
	if (!lt)
		return (NULL);
	i = 0;
	while (*str != 0)
	{
		str = ft_size_w(str, c, 1);
		if (*str != 0)
		{
			next = ft_size_w(str, c, 0);
			lt[i] = ft_substr(str, 0, next - str);
			if (!lt[i])
				return (ft_tabledel(lt, i));
			i++;
			str = next;
		}
	}
	lt[i] = 0;
	return (lt);
}

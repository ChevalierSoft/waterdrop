/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 17:55:16 by dait-atm          #+#    #+#             */
/*   Updated: 2019/11/16 17:44:55 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dlen;
	size_t	i;

	i = 0;
	while (dest[i] && i < size)
		i++;
	dlen = i;
	while (src[i - dlen] && i + 1 < size)
	{
		dest[i] = src[i - dlen];
		i++;
	}
	if (dlen < size)
		dest[i] = 0;
	return (dlen + ft_strlen(src));
}

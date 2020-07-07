/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:35:02 by dait-atm          #+#    #+#             */
/*   Updated: 2019/11/13 19:53:51 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, unsigned int n)
{
	size_t			i;
	unsigned char	d;

	i = 0;
	d = (unsigned char)c;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		if (d == ((unsigned char *)src)[i])
			return (dst + i + 1);
		i++;
	}
	return (0);
}

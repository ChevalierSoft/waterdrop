/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 21:11:13 by dait-atm          #+#    #+#             */
/*   Updated: 2019/11/19 17:47:48 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy2(char *dst, const char *src, size_t len)
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

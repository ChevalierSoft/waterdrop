/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:30:56 by dait-atm          #+#    #+#             */
/*   Updated: 2019/11/12 16:43:13 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *p;

	if ((p = malloc(size * count)) == 0)
		return (0);
	ft_bzero(p, count * size);
	((char *)p)[0] = 0;
	return (p);
}

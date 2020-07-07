/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:06:01 by dait-atm          #+#    #+#             */
/*   Updated: 2019/11/19 17:53:30 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
	ft_strncpy2(s3, s1, s1len);
	ft_strncpy2(s3 + s1len, s2, s2len);
	s3[s1len + s2len] = '\0';
	return (s3);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:59:45 by dait-atm          #+#    #+#             */
/*   Updated: 2019/11/15 17:24:11 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *v;
	t_list *u;

	v = *lst;
	if (!*lst)
		return ;
	while (v)
	{
		u = v->next;
		del(v->content);
		free(v);
		v = u;
	}
	free(lst);
	lst = NULL;
}

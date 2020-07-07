/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 23:42:34 by dait-atm          #+#    #+#             */
/*   Updated: 2019/11/19 23:43:14 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*v;
	t_list	*head;

	head = 0;
	if (lst)
	{
		v = ft_lstnew(lst->content);
		head = v;
		lst = lst->next;
		while (lst)
		{
			v = ft_lstnew(lst->content);
			f(v->content);
			ft_lstadd_back(&head, v);
			lst = lst->next;
		}
		return (head);
	}
	del(head);
	return (head);
}

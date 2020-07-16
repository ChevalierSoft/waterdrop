/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 22:52:02 by dait-atm          #+#    #+#             */
/*   Updated: 2020/07/14 23:34:52 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "waterdrop.h"

void	remove_intel(t_intel **it)
{
	if (!*it)
		return ;
	if ((*it)->map)
		remove_2d_array(&(*it)->map, (*it)->map_size->y);
	if ((*it)->filename)
		free((*it)->filename);
	if ((*it)->meta)
		remove_meta(&(*it)->meta);
	if ((*it)->ppl)
		free((*it)->ppl);
	if ((*it)->map_size)
		free((*it)->map_size);
	free(*it);
	*it = NULL;
}

t_intel	*create_intel(void)
{
	t_intel *it;

	if (!(it = malloc(sizeof(t_intel))))
		return (NULL);
	it->meta = NULL;
	it->ppl = NULL;
	it->map_size = NULL;
	if (!(it->meta = meta_init()))
		flush_quit("Error\n Not enough memory", &it, -2);
	if (!(it->ppl = malloc(sizeof(t_pos))))
		flush_quit("Error\n Not enough memory", &it, -2);
	if (!(it->map_size = malloc(sizeof(t_pos))))
		flush_quit("Error\n Not enough memory", &it, -2);
	it->map = NULL;
	it->ppl->x = -1;
	it->ppl->y = -1;
	it->ppl->o = 'x';
	it->map_size->x = 0;
	it->map_size->y = 0;
	it->map_offset = 0;
	it->fd = 0;
	return (it);
}

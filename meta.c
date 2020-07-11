/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dait-atm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 07:17:01 by dait-atm          #+#    #+#             */
/*   Updated: 2020/07/11 07:17:10 by dait-atm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "waterdrop.h"

void	aff_meta(t_meta *meta)
{
	printf("sR : %s\n", meta->str_r);
	printf("R  : ww : %d : wh  : %d\n", meta->ww, meta->wh);
	printf("NO : %s\n", meta->path_n);
	printf("SO : %s\n", meta->path_s);
	printf("EA : %s\n", meta->path_e);
	printf("WE : %s\n", meta->path_w);
	printf("SP : %s\n", meta->path_sp);
	printf("F  : %s\n", meta->path_f);
	printf("C  : %s\n", meta->path_c);
}

t_meta	*meta_init(void)
{
	t_meta *meta;

	if (!(meta = malloc(sizeof(t_meta))))
	{
		printf("Error\nNo memory for meta datas\n");
		return (NULL);
	}
	meta->ww = 0;
	meta->wh = 0;
	meta->str_r = NULL;
	meta->path_n = NULL;
	meta->path_s = NULL;
	meta->path_e = NULL;
	meta->path_w = NULL;
	meta->path_sp = NULL;
	meta->path_f = NULL;
	meta->path_c = NULL;
	return (meta);
}

void	remove_meta(t_meta **m)
{
	if (!*m)
		return ;
	if ((*m)->str_r)
		free((*m)->str_r);
	if ((*m)->path_n)
		free((*m)->path_n);
	if ((*m)->path_s)
		free((*m)->path_s);
	if ((*m)->path_e)
		free((*m)->path_e);
	if ((*m)->path_w)
		free((*m)->path_w);
	if ((*m)->path_sp)
		free((*m)->path_sp);
	if ((*m)->path_f)
		free((*m)->path_f);
	if ((*m)->path_c)
		free((*m)->path_c);
	if ((*m))
		free(*m);
}

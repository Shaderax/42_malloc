/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defrag_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 21:23:23 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/16 19:58:18 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	free_map(t_page *cur_page, t_page *prev, size_t size_m)
{
	if (prev != cur_page)
		prev->next = cur_page->next;
	else
	{
		if (size_m == TINY_MAP)
			g_maloc.tiny = NULL;
		else
			g_maloc.small = NULL;
	}
	munmap(cur_page, size_m);
}

void	defrag_mem(t_page *cur_page, size_t size_m, t_page *prev, int del)
{
	t_block 	*cur;
	t_block 	*cur_p;
	uint8_t		used;

	used = 0;
	cur = (void*)cur_page + sizeof(t_page);
	while (1)
	{
		if (!cur->size)
			break ;
		if (cur->use)
			used++;
		if (!cur->use && cur->size)
		{
			if ((void*)cur + sizeof(t_block) + cur->size < (void*)cur_page + size_m)
			{
				cur_p = (void*)cur + sizeof(t_block) + cur->size;
				if (!cur_p->use && cur_p->size)
				{
					cur->size += cur_p->size + sizeof(t_block);
					continue ;
				}
				else if (!cur_p->use && !cur_p->size && del)
				{
					cur->size = 0;
					break ;
				}
			}
		}
		cur = (void *)cur + sizeof(t_block) + cur->size;
	}
	if (!used)
		free_map(cur_page, prev, size_m);
}

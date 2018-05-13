/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defrag_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 21:23:23 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/13 22:28:28 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	defrag_mem(t_page *cur_page, size_t size_m, t_page *prev)
{
	t_block 	*cur;
	t_block 	*cur_p;
	uint8_t		used;

	used = 0;
	cur = (void*)cur_page + sizeof(t_page);
	while (1)
	{
		if ((void*)cur >= (void*)cur_page + size_m || !cur->size)
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
				else if (!cur_p->use && !cur_p->size)
					cur->size = 0;
			}
		}
		cur = (void *)cur + sizeof(t_block) + cur->size;
	}
	if (!used)
	{
		if (prev != cur_page)
			prev->next = cur_page->next;
		munmap(cur_page, size_m);
		if (size_m == TINY_MAP)
			g_maloc.tiny = NULL;
		else
			g_maloc.small = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defrag_mem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 21:23:23 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/20 07:55:17 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	free_map(t_page *cur_page, t_page *prev, size_t size_m)
{
	if (prev != cur_page)
		prev->next = cur_page->next;
	else
	{
		if (size_m == (size_t)TINY_MAP)
			g_maloc.tiny = NULL;
		else
			g_maloc.small = NULL;
	}
	munmap(cur_page, size_m);
}

int		to_defrag(t_page *cur_page, t_block *cur, size_t size_m)
{
	t_block	*cur_p;

	if ((void*)cur + sizeof(t_block) + cur->size <= (void*)cur_page + size_m - sizeof(t_block) - 1) // SEG
	{
		cur_p = (void*)cur + sizeof(t_block) + cur->size;
		if (!cur_p->use && cur_p->size)
		{
			cur->size += cur_p->size + sizeof(t_block);
			return (1);
		}
		else if (!cur_p->use && !cur_p->size)
		{
			cur->size = 0;
			return (2);
		}
	}
	return (0);
}

void	defrag_mem(t_page *cur_page, size_t size_m, t_page *prev, int del)
{
	int		c_b;
	t_block	*cur;
	size_t	used;

	del = 0;
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
			c_b = to_defrag(cur_page, cur, size_m);
			if (c_b == 1)
				continue ;
			else if (c_b == 2)
				break ;
		}
		cur = (void *)cur + sizeof(t_block) + cur->size;
	}
	if (!used)
		free_map(cur_page, prev, size_m);
}

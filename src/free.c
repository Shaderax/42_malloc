/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 18:29:49 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/22 17:06:01 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

int		find_and_free_alloc_large(void *ptr)
{
	t_page_large *cur_page;
	t_page_large *prev_page;

	cur_page = NULL;
	if ((cur_page = find_page_large(ptr, &prev_page)))
	{
		if (cur_page == g_maloc.large)
			g_maloc.large = cur_page->next;
		else
			prev_page->next = cur_page->next;
		munmap(cur_page, cur_page->size + sizeof(t_page_large));
		return (1);
	}
	return (0);
}

int		find_and_free_alloc(t_page *begin, size_t size_m, void *ptr)
{
	t_block		*cur;
	t_page		*cur_page;
	t_page		*prev;

	cur_page = begin;
	if ((cur_page = find_page(cur_page, size_m, ptr, &prev)))
	{
		if ((cur = find_ptr(cur_page, size_m, ptr)))
		{
			cur->use = 0;
			ft_bzero((void*)cur + sizeof(t_block), cur->size);
			defrag_mem(cur_page, size_m, prev, 1);
			return (1);
		}
	}
	return (0);
}

void	free(void *ptr)
{
//	ft_putstr("FREE : ");
	if (!ptr)
		return ;
	if (g_maloc.tiny && find_and_free_alloc(g_maloc.tiny, TINY_MAP, ptr))
		;
	else if (g_maloc.small &&
		find_and_free_alloc(g_maloc.small, SMALL_MAP, ptr))
		;
	else if (g_maloc.large && find_and_free_alloc_large(ptr))
		;
//	else
//		write(1, " : PAS TROUVE", 14);
//	write(1, " END \n", 1);
	return ;
}

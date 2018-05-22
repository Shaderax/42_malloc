/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 16:42:54 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/20 07:20:29 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

size_t	show(t_page *begin, size_t size_m)
{
	t_page	*cur_page;
	t_block	*cur;
	size_t	tt;

	tt = 0;
	cur_page = begin;
	cur = (void *)(cur_page) + sizeof(t_page);
	while (1)
	{
		if (!cur->size || (void*)cur >= (void *)(cur_page) + size_m)
		{
			if (!cur_page->next)
				break ;
			cur_page = cur_page->next;
			cur = (void *)(cur_page) + sizeof(t_page);
			continue ;
		}
		if (cur->use || !cur->use)
		{
			printf("%p - %p : %u octects, Use : %d\n", (void *)(cur) + sizeof(t_block), (void *)cur + cur->size + sizeof(t_block), cur->size, (cur->use & (1 << 1)) ? 1 : 0);
			tt += cur->size;
		}
		cur = (void*)(cur) + sizeof(t_block) + cur->size;
	}
	return (tt);
}

size_t	show_large(t_page_large *begin)
{
	t_page_large	*cur_page;
	size_t			tt;

	tt = 0;
	cur_page = begin;
	while (cur_page)
	{
		printf("%p - %p : %zu octects\n", (void *)(cur_page) + sizeof(t_page_large), (void *)cur_page + cur_page->size + sizeof(t_page_large), cur_page->size);
		tt += cur_page->size;
		cur_page = cur_page->next;
	}
	return (tt);
}

void	show_alloc(void)
{
	size_t tt;

	tt = 0;
	if (g_maloc.tiny)
	{
		printf("TINY : %p\n", g_maloc.tiny);
		tt += show(g_maloc.tiny, TINY_MAP);
	}
	if (g_maloc.small)
	{
		printf("SMALL : %p\n", g_maloc.small);
		tt += show(g_maloc.small, SMALL_MAP);
	}
	if (g_maloc.large)
	{
		printf("LARGE : %p\n", g_maloc.large);
		tt += show_large(g_maloc.large);
	}
	printf("Total : %zu octects\n", tt);
}

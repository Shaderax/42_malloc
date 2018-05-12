/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 18:29:49 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/12 16:31:30 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

int		find_alloc(t_page *begin, size_t size_m, void *ptr)
{
	t_block 	*cur;
	t_page 		*cur_page;

	cur_page = begin;
	while (1)
	{
		if (ptr >= (void*)(cur_page) && ptr < (void*)(cur_page) + size_m)
			break ;
		cur_page = cur_page->next;
		if (cur_page == NULL)
			return (0);
	}
	cur = (void*)cur_page + sizeof(t_page);
	while (1)
	{
		if ((void*)cur >= (void*)cur_page + size_m || cur->size == 0)
			return (0);
		if ((void*)cur + sizeof(t_block) == ptr)
		{
			if (cur->use == 0)
				return (0);
			cur->use = 0;
			return (1);
		}
		cur = (void*)cur + sizeof(t_block) + cur->size;
	}
	return 0;
}

int		find_alloc_large(void *ptr)
{
	t_page_large *cur_page;

	cur_page = g_maloc.large;
	while (1)
	{
		if (ptr < (void*)(cur_page) || ptr > (void*)(cur_page) + cur_page->size + sizeof(t_page_large))
		{
			if (cur_page->next)
				cur_page = cur_page->next;
			else
				return 0;
		}
		if ((void*)cur_page + sizeof(t_page_large) == ptr)
			return (1);
	}
	return 0;
}

void	ft_free(void *ptr)
{
	if (!ptr)
		return ;
	if (g_maloc.tiny && find_alloc(g_maloc.tiny, TINY_MAP, ptr))
		return ;
	else if (g_maloc.small && find_alloc(g_maloc.small, SMALL_MAP, ptr))
		return ;
//	else if (g_maloc.large && find_alloc_large(ptr))
//		return ;
	printf("PAS TROUVE\n");
	return ;
}

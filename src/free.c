/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 18:29:49 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/13 00:47:57 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

void	*find_page(t_page *cur_page, size_t size_m, void *ptr, t_page **prev)
{
	while (1)
	{
		if (ptr >= (void*)(cur_page) && ptr < (void*)(cur_page) + size_m)
			break ;
		(*prev) = cur_page;
		cur_page = cur_page->next;
		if (cur_page == NULL)
			return (NULL);
	}
	return (cur_page);
}

void	*find_ptr(t_page *cur_page, size_t size_m, void *ptr)
{
	t_block 	*cur;

	cur = (void*)cur_page + sizeof(t_page);
	while (1)
	{
		if ((void*)cur >= (void*)cur_page + size_m || cur->size == 0)
			return (NULL);
		if ((void*)cur + sizeof(t_block) == ptr)
		{
			if (cur->use == 0)
				return (NULL);
			cur->use = 0;
			return (cur);
		}
		cur = (void*)cur + sizeof(t_block) + cur->size;
	}
}

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
			}
			else if (!used && (void *)cur + sizeof(t_block) + cur->size == (void*)cur_page + size_m)
				cur->size = 0;
		}
		cur = (void *)cur + sizeof(t_block) + cur->size;
	}
	if (!used)
	{
		if (prev != cur_page)
			prev->next = cur_page->next;
		munmap(cur_page, size_m);
	}
}

int		find_alloc(t_page *begin, size_t size_m, void *ptr)
{
	t_block 	*cur;
	t_page 		*cur_page;
	t_page 		*prev;

	cur_page = begin;
	if ((cur_page = find_page(cur_page, size_m, ptr, &prev)))
		if ((cur = find_ptr(cur_page, size_m, ptr)))
		{
			defrag_mem(cur_page, size_m, prev);
			return (1);
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
	else if (g_maloc.large && find_alloc_large(ptr))
		return ;
	printf("PAS TROUVE\n");
	return ;
}

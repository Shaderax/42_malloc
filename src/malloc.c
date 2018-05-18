/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 13:00:26 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/18 20:30:18 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

t_maloc		g_maloc = {NULL, NULL, NULL, {0}};

// BZERO LA MEM

void	*place_2_blocks(t_block *cur, size_t size)
{
	int size_tmp;

	size_tmp = cur->size - size - sizeof(t_block);
	cur = (void*)cur + size + sizeof(t_block);
	cur->use = 0;
	cur->size = size_tmp;
	cur = (void*)cur - size - sizeof(t_block);
	cur->size = size;
	cur->use = 1;
	return ((void *)cur + sizeof(t_block));
}

void	*alloc_tiny_small(size_t size, size_t size_m, t_page **b_page)
{
	t_block	*cur;
	t_page	*cur_page;

	if (!(*b_page))
		*b_page = mmap(NULL, size_m, PROT_MMAP, FLAG_MMAP, -1, 0);
	cur_page = *b_page;
	while (1)
	{
		cur = find_place(cur_page, size_m, size);
		if ((void*)cur >= (void *)cur_page + size_m ||
				(unsigned long)((void*)cur_page + size_m - (void *)cur) <
					size + sizeof(t_block))
		{
			if (!cur_page->next)
				cur_page->next = mmap(NULL, size_m, PROT_MMAP,
					FLAG_MMAP, -1, 0);
			cur_page = cur_page->next;
			continue ;
		}
		else if (size + sizeof(t_block) + 1 <= cur->size)
			return (place_2_blocks(cur, size));
		cur->use = 1;
		cur->size = size;
		return ((void *)cur + sizeof(t_block));
	}
}

void	*alloc_large(size_t size)
{
	t_page_large *cur_page;

	if (!g_maloc.large)
	{
		g_maloc.large = mmap(NULL, size, PROT_MMAP,
			FLAG_MMAP, -1, 0);
		cur_page = g_maloc.large;
	}
	else
	{
		cur_page = g_maloc.large;
		while (cur_page->next)
			cur_page = cur_page->next;
		if (!cur_page->next)
			cur_page->next = mmap(NULL, size, PROT_MMAP,
				FLAG_MMAP, -1, 0);
		cur_page = cur_page->next;
	}
	cur_page->size = size;
	return ((void*)cur_page + sizeof(t_page_large));
}

void	*malloc(size_t size)
{
	while (1);
	if (size <= 0)
		return (NULL);
	if (size <= MAX_TINY)
		return (alloc_tiny_small(size, TINY_MAP, &g_maloc.tiny));
	else if (size <= MAX_SMALL)
		return (alloc_tiny_small(size, SMALL_MAP, &g_maloc.small));
	else
		alloc_large(size);
	return (NULL);
}

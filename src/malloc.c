/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 13:00:26 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/06/13 10:45:10 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

t_maloc			g_maloc = {NULL, NULL, NULL};
pthread_mutex_t	g_malloc_lock;

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

void	*new_page(size_t size_m, t_page *cur_page)
{
	if (!cur_page->next)
	{
		if (size_m == (size_t)TINY_MAP)
		{
			cur_page = g_maloc.tiny;
			if ((g_maloc.tiny = mmap(NULL, size_m, PROT_MMAP,
				FLAG_MMAP, -1, 0)) == MAP_FAILED)
				return (NULL);
			g_maloc.tiny->next = cur_page;
			cur_page = g_maloc.tiny;
			return (cur_page);
		}
		else
		{
			cur_page = g_maloc.small;
			if ((g_maloc.small = mmap(NULL, size_m,
				PROT_MMAP, FLAG_MMAP, -1, 0)) == MAP_FAILED)
				return (NULL);
			g_maloc.small->next = cur_page;
			cur_page = g_maloc.small;
			return (cur_page);
		}
	}
	cur_page = cur_page->next;
	return (cur_page);
}

void	*alloc_tiny_small(size_t size, size_t size_m, t_page **b_page)
{
	t_block	*cur;
	t_page	*cur_page;

	if (!(*b_page) && (*b_page = mmap(NULL, size_m,
		PROT_MMAP, FLAG_MMAP, -1, 0)) == MAP_FAILED)
		return (NULL);
	cur_page = *b_page;
	while (1)
	{
		cur = find_place(cur_page, size_m, size);
		if ((void*)cur >= MAX_PAGE || (unsigned long)(MAX_PAGE - (void *)cur) <
					size + sizeof(t_block))
		{
			cur_page = new_page(size_m, cur_page);
			if (!(cur_page))
				return (NULL);
			else
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
		if ((g_maloc.large = mmap(NULL, size + sizeof(t_page_large), PROT_MMAP,
			FLAG_MMAP, -1, 0)) == MAP_FAILED)
			return (NULL);
		cur_page = g_maloc.large;
	}
	else
	{
		cur_page = g_maloc.large;
		while (cur_page->next)
			cur_page = cur_page->next;
		if (!cur_page->next)
			if ((cur_page->next = mmap(NULL, size + sizeof(t_page_large),
				PROT_MMAP, FLAG_MMAP, -1, 0)) == MAP_FAILED)
				return (NULL);
		cur_page = cur_page->next;
	}
	cur_page->size = size;
	return ((void*)cur_page + sizeof(t_page_large));
}

void	*malloc(size_t size)
{
	void *ret;

	ret = NULL;
	if (size <= 0)
		size = 1;
	size += (ALIGN - (size + sizeof(t_block)) % ALIGN);
	pthread_mutex_lock(&g_malloc_lock);
	if (size <= MAX_TINY)
		ret = (void*)alloc_tiny_small(size, TINY_MAP, &g_maloc.tiny);
	else if (size <= MAX_SMALL)
		ret = (void*)alloc_tiny_small(size, SMALL_MAP, &g_maloc.small);
	else
		ret = (void*)alloc_large(size);
	pthread_mutex_unlock(&g_malloc_lock);
	return (ret);
}

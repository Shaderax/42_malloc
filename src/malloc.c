/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 13:00:26 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/23 18:02:24 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

t_maloc		g_maloc = {NULL, NULL, NULL};

/* NEED TO CHECK PLACE 2 BLOCK */

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
		if ((void*)cur >= MAX_PAGE ||
				(unsigned long)(MAX_PAGE - (void *)cur) <
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
		g_maloc.large = mmap(NULL, size + sizeof(t_page_large), PROT_MMAP,
			FLAG_MMAP, -1, 0);
		cur_page = g_maloc.large;
	}
	else
	{
		cur_page = g_maloc.large;
		while (cur_page->next)
			cur_page = cur_page->next;
		if (!cur_page->next)
			cur_page->next = mmap(NULL, size + sizeof(t_page_large), PROT_MMAP,
				FLAG_MMAP, -1, 0);
		cur_page = cur_page->next;
	}
	cur_page->size = size;
	return ((void*)cur_page + sizeof(t_page_large));
}

void	*malloc(size_t size)
{
	void*	ret;
//	ft_putstr("MALLOC : ");
//	ft_putnbr(size);
//	ft_putstr("\n");
	if (size <= 0)
		size = 1;
	size += (8 - (size + sizeof(t_block)) % 8);
//	ft_putnbr(size);
//	ft_putstr("\n");
	if (size <= MAX_TINY)
	{
//		ft_putstr("END\n");
		ret = (void*)alloc_tiny_small(size, TINY_MAP, &g_maloc.tiny);
		return ((void*)ret);
	}
	else if (size <= MAX_SMALL)
	{
//		ft_putstr("END\n");
		ret = (void*)alloc_tiny_small(size, SMALL_MAP, &g_maloc.small);
		return ((void*)ret);
	}
	else
	{
//		ft_putstr("END\n");
		ret = (void*)alloc_large(size);
		return ((void*)ret);
	}
	return (NULL);
}

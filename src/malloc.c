/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 13:00:26 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/12 15:17:09 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

t_maloc		g_maloc = {NULL, NULL, NULL};

void	*alloc_tiny_small(size_t size, size_t size_m, t_page **b_page)
{
	t_block	*cur;
	t_page *cur_page;
	
	if (!(*b_page))
		(*b_page) = mmap(NULL, size_m, PROT_READ | PROT_WRITE,
			   	MAP_ANON | MAP_PRIVATE, -1, 0);
	cur_page = (*b_page);
	while (1)
	{
		cur = (void *)cur_page + sizeof(t_page);
		while ((void*)cur < (void *)cur_page + size_m && cur->use && (cur->size < size || (void*)cur_page + size_m - (void *)cur > size + sizeof(t_block)))
			cur = (void*)cur + sizeof(t_block) + cur->size;
		if ((void*)cur >= (void *)cur_page + size_m || (void*)cur_page + size_m - (void *)cur < size + sizeof(t_block))
		{
			if (!cur_page->next)
				cur_page->next = mmap(NULL, size_m, PROT_READ | PROT_WRITE,
					   	MAP_ANON | MAP_PRIVATE, -1, 0);
			cur_page = cur_page->next;
			continue ;
		}
		cur->size = size;
		cur->use = 1;
		return ((void *)cur + sizeof(t_block));
	}
}
void	*alloc_large(size_t size)
{
	t_page_large *cur_page;
	
	if (!g_maloc.large)
	{
		g_maloc.large = mmap(NULL, size, PROT_READ | PROT_WRITE,
			   	MAP_ANON | MAP_PRIVATE, -1, 0);
		cur_page = g_maloc.large;
	}
	else
	{
		cur_page = g_maloc.large;
		while (cur_page->next)
			cur_page = cur_page->next;
		if (!cur_page->next)
			cur_page->next = mmap(NULL, size, PROT_READ | PROT_WRITE,
				   	MAP_ANON | MAP_PRIVATE, -1, 0);
		cur_page = cur_page->next;
	}
	cur_page->size = size;
	return ((void*)cur_page + sizeof(t_page_large));
}

void	*ft_malloc(size_t size)
{
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

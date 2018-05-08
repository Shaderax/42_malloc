/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 13:00:26 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/08 16:22:28 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

t_maloc		g_maloc = {NULL, NULL, NULL};

void	*alloc_tiny(size)
{
	t_block	*cur;
	t_page *cur_page;
	
	if (!g_maloc.tiny)
		g_maloc.tiny = mmap(NULL, TINY_MAP, PROT_READ | PROT_WRITE,
			   	MAP_ANON | MAP_PRIVATE, -1, 0);
	cur_page = g_maloc.tiny;
	cur = (void *)(g_maloc.tiny + sizeof(t_page));
	while (cur != (void *)(g_maloc.tiny + TINY_MAP) && cur->use && cur->size && cur->size >= size && (void*)(g_maloc.tiny + TINY_MAP) - (void *)cur > size + sizeof(t_block))
		cur = cur + sizeof(t_block) + cur->size;
	if (cur != (void *)(g_maloc.tiny + TINY_MAP))
	{
		cur->size = size;
		cur->use = 1;
	}
	else if (cur_page->next)
	{

	}
	return cur + sizeof(t_block);
}

void	*ft_malloc(size_t size)
{
	if (size <= MAX_TINY)
		return (alloc_tiny(size));
//	else if (size <= MAX_SMALL)
//		alloc_small(size);
//	else
//		alloc_large(size);
	return (NULL);
}

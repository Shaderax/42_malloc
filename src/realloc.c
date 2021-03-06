/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:24:53 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/06/13 11:11:45 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*search_and_copy_large(void *ptr, size_t size_r)
{
	void			*ret;
	t_page_large	*cur_page;
	t_page_large	*prev;

	if ((cur_page = find_page_large(ptr, &prev)))
	{
		if (size_r == cur_page->size)
			return (ptr);
		ret = malloc(size_r);
		if (!ret)
			return (NULL);
		ft_memcpy((void*)ret, (void*)cur_page + sizeof(t_page_large),
			size_r <= cur_page->size ? size_r : cur_page->size);
		if (cur_page == g_maloc.large)
			g_maloc.large = cur_page->next;
		else
			prev->next = cur_page->next;
		munmap(cur_page, cur_page->size + sizeof(t_page_large));
		return (ret);
	}
	return (NULL);
}

void	*search_and_copy(t_page *begin, size_t size_m, void *ptr, size_t size_r)
{
	t_block *cur;
	void	*ret;
	t_page	*cur_page;
	t_page	*prev;

	cur_page = begin;
	if ((cur_page = find_page(cur_page, size_m, ptr, &prev)))
	{
		if ((cur = find_ptr(cur_page, size_m, ptr)))
		{
			if (size_r == cur->size)
				return (ptr);
			ret = malloc(size_r);
			cur->use = 0;
			ft_memcpy(ret, (void*)cur + sizeof(t_block),
				size_r <= cur->size ? size_r : cur->size);
			defrag_mem(cur_page, size_m, prev, 1);
			return (ret);
		}
	}
	return (NULL);
}

void	*realloc(void *ptr, size_t size)
{
	void *ret;

	if (size <= 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (malloc(size));
	size += (ALIGN - (size + sizeof(t_block)) % ALIGN);
	ret = NULL;
	pthread_mutex_lock(&g_malloc_lock);
	if (g_maloc.tiny &&
		(ret = search_and_copy(g_maloc.tiny, TINY_MAP, ptr, size)))
		;
	else if (g_maloc.small &&
		(ret = search_and_copy(g_maloc.small, SMALL_MAP, ptr, size)))
		;
	else if (g_maloc.large && (ret = search_and_copy_large(ptr, size)))
		;
	pthread_mutex_unlock(&g_malloc_lock);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:24:53 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/18 19:44:46 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*search_and_copy_large(void	*ptr, size_t size_r)
{
	void			*ret;
	t_page_large	*cur_page;
	t_page_large	*prev;

	if ((cur_page = find_page_large(ptr, &prev)))
	{
		ret = malloc(size_r);
		ft_memcpy(ret, (void*)cur_page + sizeof(t_page_large),
			   	size_r <= cur_page->size ? size_r : cur_page->size);
		free(cur_page);
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
			cur->use = 0;
			ret = malloc(size_r);
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

	if (!ptr || size <= 0)
		return (NULL);
	if (g_maloc.tiny &&
			(ret = search_and_copy(g_maloc.tiny, TINY_MAP, ptr, size)))
		return (ret);
	else if (g_maloc.small &&
			(ret = search_and_copy(g_maloc.small, SMALL_MAP, ptr, size)))
		return (ret);
	else if (g_maloc.large && search_and_copy_large(ptr, size))
		;
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_finder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 01:02:02 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/06/12 15:33:08 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*find_page_large(void *ptr, t_page_large **prev_page)
{
	t_page_large *cur_page;

	cur_page = g_maloc.large;
	*prev_page = cur_page;
	while (1)
	{
		if (ptr < (void*)(cur_page) ||
			ptr > (void*)(cur_page) + cur_page->size + sizeof(t_page_large))
		{
			*prev_page = cur_page;
			if (cur_page->next)
				cur_page = cur_page->next;
			else
				return (NULL);
			continue ;
		}
		if ((void*)cur_page + sizeof(t_page_large) == ptr)
			return (cur_page);
		else
			return (NULL);
	}
	return (NULL);
}

void	*find_page(t_page *cur_page, size_t size_m, void *ptr, t_page **prev)
{
	(*prev) = cur_page;
	while (1)
	{
		if (ptr >= (void*)(cur_page) && ptr <= MAX_PAGE)
			break ;
		(*prev) = cur_page;
		cur_page = cur_page->next;
		if (!cur_page)
			return (NULL);
	}
	return (cur_page);
}

void	*find_ptr(t_page *cur_page, size_t size_m, void *ptr)
{
	t_block *cur;

	cur = MIN_PAGE;
	while (1)
	{
		if ((void*)cur >= MAX_PAGE || !cur->size)
			return (NULL);
		if ((void*)cur + sizeof(t_block) == ptr)
		{
			if (cur->use == 0)
				return (NULL);
			return (cur);
		}
		cur = (void*)cur + sizeof(t_block) + cur->size;
	}
	return (NULL);
}

void	*find_place(t_page *cur_page, size_t size_m, size_t size)
{
	t_block *cur;

	cur = MIN_PAGE;
	while (1)
	{
		if ((void*)cur >= MAX_PAGE ||
			(unsigned long)(MAX_PAGE - (void *)cur) <
				size + sizeof(t_block))
			break ;
		if (!cur->use && (!cur->size || cur->size == size ||
			size + sizeof(t_block) + 1 <= cur->size))
			break ;
		cur = (void*)cur + sizeof(t_block) + cur->size;
	}
	return (cur);
}

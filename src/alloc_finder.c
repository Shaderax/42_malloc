/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_finder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 01:02:02 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/14 01:03:23 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*find_page(t_page *cur_page, size_t size_m, void *ptr, t_page **prev)
{
	(*prev) = cur_page;
	while (1)
	{
		if (ptr >= (void*)(cur_page) && ptr <= (void*)(cur_page) + size_m)
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
			return (cur);
		}
		cur = (void*)cur + sizeof(t_block) + cur->size;
	}
}

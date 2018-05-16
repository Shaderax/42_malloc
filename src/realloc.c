/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:24:53 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/16 19:59:43 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

//void	*alloc_to_broaden(t_block *cur, t_block *check_next, size_t size_r)
//{
//	int	size_tmp;
//
//	size_tmp = cur->size + sizeof(t_block) + check_next->size - size_r;
//	if (cur->size + sizeof(t_block) + check_next->size == size_r)
//	{
//		cur->size = size_r;
//		check_next->size = 0;
//	}
//	else if (cur->size + sizeof(t_block) + check_next->size >= size_r + sizeof(t_block) + 1)
//	{
//		cur->use = 1;
//		cur->size = size_r;
//		check_next = (void*)cur + cur->size + sizeof(t_block);
//		check_next->size = size_tmp;
//		check_next->use = 0;
//	}
//	return ((void*)cur + sizeof(t_block));
//}
//
//void	*resize(t_page *cur_page, t_block *cur, size_t size_m, size_t size_r)
//{
//	t_block *check_next;
//
//	if ((size_m == TINY_MAP && size_r > MAX_TINY) || (size_m == SMALL_MAP && size_r > MAX_SMALL))
//		return (NULL);
//	// FUNCTION REBIRTH
//	
//	
//	
//	if ((void*)cur + size_r + sizeof(t_block) > (void*)cur_page + sizeof(t_page) + size_m) // rentre pas dans ma page
//		return (NULL);
//	check_next = (void*)cur + sizeof(t_block) + cur->size;
//	if (!check_next->use && check_next->size)
//		if (cur->size + sizeof(t_block) + check_next->size == size_r || cur->size + sizeof(t_block) + check_next->size >= size_r + sizeof(t_block) + 1)
//			return alloc_to_broaden(cur, check_next, size_r);
//	if (!check_next->use && !check_next->size && (void*)cur < (void*)cur_page + sizeof(t_block) + size_m)
//		cur->size = size_r;
//	else if (check_next->use && )
//	return ((void*)cur + sizeof(t_block));
//}

void	*search_and_copy(t_page *begin, size_t size_m, void *ptr, size_t size_r)
{
	t_block *cur;
	void 	*ret;
	t_page	*cur_page;
	t_page	*prev;

	cur_page = begin;
	if ((cur_page = find_page(cur_page, size_m, ptr, &prev)))
	{
		if ((cur = find_ptr(cur_page, size_m, ptr)))
		{
			cur->use = 0;
			ret = ft_malloc(size_r);
			ft_memcpy(ret, (void*)cur + sizeof(t_block), size_r <= cur->size ? size_r : cur->size);
			defrag_mem(cur_page, size_m, prev, 1);
			return (ret);
		}
	}
	return NULL;
}

//			if ((ret = resize(cur_page, cur, size_m, size_r)))
//				return (ret);

void	*ft_realloc(void *ptr, size_t size)
{
	void *ret;

	if (!ptr || size <= 0)
		return (NULL);

	if (g_maloc.tiny)
		return search_and_copy(g_maloc.tiny, TINY_MAP, ptr, size);
//	if (g_maloc.tiny && (ret = search_and_copy(g_maloc.tiny, TINY_MAP, ptr, size)))
//		return (ret);
//	else if (g_maloc.small && (ret = search_and_copy(g_maloc.small, SMALL_MAP, ptr, size)))
//		return (ret);
//	else if (g_maloc.large && search_and_copy_large())
	return (NULL);
	
}

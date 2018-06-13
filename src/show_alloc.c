/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 16:42:54 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/06/13 11:28:25 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	show_block(void *beg, void *end, size_t size)
{
	ft_putstr("0x");
	ft_print_addr((unsigned long long)beg);
	ft_putstr(" - ");
	ft_putstr("0x");
	ft_print_addr((unsigned long long)end);
	ft_putstr(" : ");
	ft_putnbr(size);
	ft_putstr(" octets\n");
}

size_t	show(t_page *begin, size_t size_m)
{
	t_page	*cur_page;
	t_block	*cur;
	size_t	tt;

	tt = 0;
	cur_page = begin;
	cur = (void *)(cur_page) + sizeof(t_page) + OFFSET;
	while (1)
	{
		if (!cur->size || (void*)cur >= (void *)(cur_page) + size_m)
		{
			if (!cur_page->next)
				break ;
			cur_page = cur_page->next;
			cur = (void *)(cur_page) + sizeof(t_page) + OFFSET;
			continue ;
		}
		if (cur->use || !cur->use)
			show_block((void *)(cur) + sizeof(t_block),
				(void *)cur + cur->size + sizeof(t_block), cur->size);
		if (cur->use || !cur->use)
			tt += cur->size;
		cur = (void*)(cur) + sizeof(t_block) + cur->size;
	}
	return (tt);
}

size_t	show_large(t_page_large *begin)
{
	t_page_large	*cur_page;
	size_t			tt;

	tt = 0;
	cur_page = begin;
	ft_putstr("LARGE");
	ft_putstr(" : 0x");
	ft_print_addr((unsigned long long)begin);
	ft_putstr("\n");
	while (cur_page)
	{
		show_block((void *)(cur_page) + sizeof(t_page_large),
			(void *)cur_page + cur_page->size + sizeof(t_page_large),
				cur_page->size);
		tt += cur_page->size;
		cur_page = cur_page->next;
	}
	return (tt);
}

size_t	print_alloc(char *page_name, void *ptr, int size)
{
	size_t total_oct;

	total_oct = 0;
	ft_putstr(page_name);
	ft_putstr(" : 0x");
	ft_print_addr((unsigned long long)ptr);
	ft_putstr("\n");
	if (size)
		return ((total_oct += show(ptr, size)));
	else
		return ((total_oct += show_large(ptr)));
}

void	show_alloc_mem(void)
{
	size_t total_oct;

	pthread_mutex_lock(&g_malloc_lock);
	total_oct = 0;
	if (g_maloc.tiny)
		total_oct += print_alloc("TINY", g_maloc.tiny, TINY_MAP);
	if (g_maloc.small)
		total_oct += print_alloc("SMALL", g_maloc.small, SMALL_MAP);
	if (g_maloc.large)
		total_oct += show_large(g_maloc.large);
	ft_putstr("Total : ");
	ft_putnbr(total_oct);
	ft_putstr(" octects\n");
	pthread_mutex_unlock(&g_malloc_lock);
}

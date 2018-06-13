/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 16:03:14 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/06/13 11:11:25 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc(size_t count, size_t size)
{
	void	*ret;
	size_t	len;

	pthread_mutex_lock(&g_malloc_lock);
	len = count * size;
	if (size != 0 && len / size != count)
		return (NULL);
	if (!(ret = malloc(len)))
		return (NULL);
	if (len <= 0)
		len = 1;
	len += (ALIGN - (len + sizeof(t_block)) % ALIGN);
	ft_bzero(ret, len);
	pthread_mutex_unlock(&g_malloc_lock);
	return (ret);
}

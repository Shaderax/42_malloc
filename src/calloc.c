/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 16:03:14 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/25 15:58:28 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc(size_t count, size_t size)
{
	void	*ret;
	size_t	len;

	len = count * size;
	if (!(ret = malloc(len)))
		return (NULL);
	if (len <= 0)
		len = 1;
	len += (ALIGN - (len + sizeof(t_block)) % ALIGN);
	ft_bzero(ret, len);
	return (ret);
}

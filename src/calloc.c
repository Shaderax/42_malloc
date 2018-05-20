/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 16:03:14 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/20 20:14:17 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_calloc(size_t count, size_t size)
{
	ft_putstr("CALLOC ");
	ft_putnbr(count);
	ft_putstr(" ");
	ft_putnbr(size);
	ft_putstr("\n");

	void	*ret;
	int		ss;

	if (!count || !size)
		return (NULL);
	ss = count * size;
	if (size != ss / count)
		return (NULL);
	ret = ft_malloc(count * size);
	if (!ret)
		return (NULL);
	ft_memset(ret, 0, ss);
	return (ret);
}

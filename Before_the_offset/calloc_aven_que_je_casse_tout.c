/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 16:03:14 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/21 17:30:12 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*calloc(size_t count, size_t size)
{
	ft_putstr("CALLOC ");
	ft_putnbr(count);
	ft_putstr(" ");
	ft_putnbr(size);
	ft_putstr("\n");

	void	*ret;

	if (!count || !size)
		return (NULL);
	if (!(ret = malloc(count * size)))
		return (NULL);
	ft_bzero(ret, count * size);
	return (ret);
}

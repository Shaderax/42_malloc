/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 16:03:14 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/22 14:23:12 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#define ALIGNE sizeof(size_t)

void	*calloc(size_t count, size_t size)
{
	ft_putstr("CALLOC ");
	ft_putnbr(count);
	ft_putstr(" ");
	ft_putnbr(size);
	ft_putstr("\n");

	void	*ret;
//	size_t	rr;
	size_t	len;

	if (!count || !size)
		return (NULL);
	len = count * size;
	if (!(ret = malloc(len)))
		return (NULL);
	ft_bzero(ret, len);
//	rr = (size_t)ret;
//	rr /= ALIGNE;
//	rr *= ALIGNE;
//	ret = (void*)rr;
//	ft_putnbr(((int)ret % 8));
	ft_putstr("END\n");
	return ((void*)ret);
}

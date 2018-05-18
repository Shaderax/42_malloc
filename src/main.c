/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 16:30:37 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/18 20:21:32 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "malloc.h"

int main(int argc, char **argv)
{
	int i;
	char *addr;

	i = 0;
	while (i < 1024)
		i++;
	return (0);
//	int nb_i = 10024;
//	char *str[nb_i];
//
//	int i = -1;
//	argc = 0;
//	argv = 0;
//	printf("Size of page : %d\n", getpagesize());
//	while (++i < nb_i)
//	{
//		str[i]  = malloc(1024);
//		*str[i] = 42;
//	}
//	i = -1;
//	while (++i < nb_i)
//	{
//		free(str[i++]);
//		free(str[i++]);
//	}
//	show_alloc();
//	str[0] = ft_malloc(30);
//	str[1] = ft_malloc(30);
//	str[2] = ft_malloc(30);
//	str[3] = ft_malloc(30);
//	show_alloc();
//	ft_strcpy(str[0], "JE SUIS SUISSE!");
//	str[0] = ft_realloc(str[0], 20);
//	show_alloc();
//	str[0] = ft_realloc(str[0], 30);
//	show_alloc();
//	ft_free(str[0]);
//	str[3] = ft_realloc(str[3], 3);
//	show_alloc();
}

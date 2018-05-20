/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 16:30:37 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/20 21:06:35 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "malloc.h"

#define TINY_MALLOCED 10000
#define SMALL_MALLOCED 10000
#define LARGE_MALLOCED 10000

void print(char *s)
{
	write(1, s, strlen(s));
}

int main(int argc, char **argv)
{
	srand (time (NULL));
	int index;
	int rande;

	char *tiny[TINY_MALLOCED];
	char *small[SMALL_MALLOCED];
	char *large[LARGE_MALLOCED];

	index = -1;
	while (++index < TINY_MALLOCED - 1)
		tiny[index] = ft_malloc((int)(rand() / (double)RAND_MAX * (MAX_TINY - 1)));
	index = -1;
	while (++index < SMALL_MALLOCED)
		small[index] = ft_malloc((int)(rand() / (double)RAND_MAX * (MAX_SMALL - 1)));
	index = -1;
	while (++index < LARGE_MALLOCED)
		large[index] = ft_malloc((int)(rand() / (double)RAND_MAX * (300000 - 1)));

	index = -1;
	rande = (int)(rand() / (double)RAND_MAX * (TINY_MALLOCED - 1));
	while (++index < rande)
		ft_free(tiny[(int)(rand() / (double)RAND_MAX * (TINY_MALLOCED - 1))]);
	index = -1;
	rande = (int)(rand() / (double)RAND_MAX * (SMALL_MALLOCED - 1));
	while (++index < rande)
		ft_free(small[(int)(rand() / (double)RAND_MAX * (SMALL_MALLOCED - 1))]);
	index = -1;
	rande = (int)(rand() / (double)RAND_MAX * (LARGE_MALLOCED - 1));
	while (++index < rande)
		ft_free(large[(int)(rand() / (double)RAND_MAX * (LARGE_MALLOCED - 1))]);
//	show_alloc();
	index = -1;
	rande = (int)(rand() / (double)RAND_MAX * (LARGE_MALLOCED - 1));
	while (++index < rande)
		large[index] = ft_realloc(large[index], (int)(rand() / (double)RAND_MAX * (LARGE_MALLOCED - 1)));









	int i;
	char *addr;
	char *str[4];

//	i = 0;
	/* FIRST TEST */
	
//		while (i < 1024)
//			i++;
//		return (0);


	/* SECOND TEST */
//		while (i < 0)
//		{
//			addr = (char *)ft_malloc(1024);
//			addr[0] = 42;
//			i++;
//		}

	/* TEST 3 */
//	char *addr1;
//	char *addr3;
//
//	addr1 = (char*)ft_malloc(16*M);
//	strcpy(addr1, "Bonjours\n");
//	print(addr1);
//	addr3 = (char*)ft_realloc(addr1, 128*M);
//	addr3[127*M] = 42;
//	print(addr3);
//	return (0);

	/* TEST 4 */
//		char *addr1;
//		char *addr2;
//		char *addr3;
//	
//		addr1 = (char*)ft_malloc(16*M);
//		strcpy(addr1, "Bonjours\n");
//		print(addr1);
//		addr2 = (char*)ft_malloc(16*M);
//		addr3 = (char*)ft_realloc(addr1, 128*M);
//		addr3[127*M] = 42;
//		print(addr3);
//		return (0);

	/* TEST ERROR */
//	addr = ft_malloc(16);
//	ft_free(NULL);
//	ft_free((void *)addr + 5);
//	if (ft_realloc((void *)addr + 5, 10) == NULL)
//		print("Bonjours\n");

	/* SHOW_ALLOC */
//	ft_malloc(1024);
//	ft_malloc(1024 * 32);
//	ft_malloc(1024 * 1024);
//	ft_malloc(1024 * 1024 * 16);
//	ft_malloc(1024 * 1024 * 128);
//	show_alloc();
//	return (0);


	/* TEST DOUBLE FREE */
//	int nb_i = 10024;
//	char *str[nb_i];
//
//	i = -1;
//	argc = 0;
//	argv = 0;
//	printf("Size of page : %d\n", getpagesize());
//	while (++i < nb_i)
//	{
//		str[i]  = ft_malloc(1024);
//		*str[i] = 42;
//	}
//	i = -1;
//	while (++i < nb_i)
//	{
//		ft_free(str[i++]);
//		ft_free(str[i++]);
//	}
//	show_alloc();
	/* TEST */
//	str[0] = ft_malloc(49600);
//	str[1] = ft_malloc(300000);
//	str[2] = ft_malloc(354520);
//	str[3] = ft_malloc(30);
//	show_alloc();
//	ft_free(str[2]);
//	show_alloc();
//	ft_free(str[0]);
//	show_alloc();
//	ft_free(str[1]);
//	str[0] = ft_realloc(str[0], 20);
//	show_alloc();
//	str[0] = ft_realloc(str[0], 30);
//	show_alloc();
//	ft_free(str[0]);
//	str[3] = ft_realloc(str[3], 3);
//	show_alloc();
}

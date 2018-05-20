/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 16:30:37 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/20 06:03:58 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M (1024 * 1024)

void print(char *s)
{
	write(1, s, strlen(s));
}

int main(int argc, char **argv)
{
	int i;
	char *addr;

	i = 0;
	/* FIRST TEST */
		while (i < 1024)
			i++;
		return (0);

	/* SECOND TEST */
//		while (i < 0)
//		{
//			addr = (char *)malloc(1024);
//			addr[0] = 42;
//			i++;
//		}
	/* TEST 3 */
//	char *addr1;
//	char *addr3;
//
//	addr1 = (char*)malloc(16*M);
//	strcpy(addr1, "Bonjours\n");
//	print(addr1);
//	addr3 = (char*)realloc(addr1, 128*M);
//	addr3[127*M] = 42;
//	print(addr3);
//	return (0);

	/* TEST 4 */
//	char *addr1;
//	char *addr2;
//	char *addr3;
//
//	addr1 = (char*)malloc(16*M);
//	strcpy(addr1, "Bonjours\n");
//	print(addr1);
//	addr2 = (char*)malloc(16*M);
//	addr3 = (char*)realloc(addr1, 128*M);
//	addr3[127*M] = 42;
//	print(addr3);
//	return (0);

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

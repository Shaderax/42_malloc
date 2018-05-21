/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 19:19:08 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/21 17:25:21 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

#include "../libft/libft/includes/libft.h"
#include <sys/mman.h>

#define MAX_TINY	496
#define MAX_SMALL	15359
#define PAGE_SIZE	getpagesize()

#define TINY_MAP	150	* PAGE_SIZE
#define SMALL_MAP	400	* PAGE_SIZE

#define PROT_MMAP	PROT_READ | PROT_WRITE
#define FLAG_MMAP	MAP_ANON | MAP_PRIVATE

typedef struct s_block	t_block;
typedef struct s_page	t_page;
typedef struct s_page_large	t_page_large;
typedef struct s_maloc	t_maloc;

struct			s_block
{
	uint32_t	size : 31;
	int8_t		use : 1;
};

struct	s_page
{
	t_page	*next;
};

struct	s_page_large
{
	t_page_large	*next;
	size_t			size;
	char			utab[4];
};

struct 	s_maloc
{
	t_page *tiny;
	t_page *small;
	t_page_large *large;
	char	utab[8];
};

extern t_maloc			g_maloc;

void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	*calloc(size_t count, size_t size);
void	free(void	*ptr);

void	show_alloc();
void	defrag_mem(t_page *cur_page, size_t size_m, t_page *prev, int del);

void	*find_page(t_page *cur_page, size_t size_m, void *ptr, t_page **prev);
void	*find_ptr(t_page *cur_page, size_t size_m, void *ptr);
void	*find_place(t_page *cur_page, size_t size_m, size_t size);
void	*find_page_large(void *ptr, t_page_large **prev_page);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 19:19:08 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/05/03 17:36:31 by nrouzeva         ###   ########.fr       */
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

typedef struct s_block	t_block;
typedef struct s_page	t_page;
typedef struct s_maloc	t_maloc;

struct			s_block
{
	uint32_t	size : 31;
	int8_t		free : 1;
};

struct	s_page
{
	t_page	*next;
};

struct 	s_maloc
{
	t_page *tiny;
	t_page *small;
	t_page *large;
};

extern t_maloc			g_maloc;

void	*ft_malloc(size_t size);

#endif
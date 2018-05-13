#include "malloc.h"

void	find_new_place()
{

}

void	*search_and_copy(t_page *begin, size_t size_m, void *ptr, size_t size_r)
{
	t_block *cur;
	t_page	*cur_page;
	t_page	*prev;

	cur_page = begin;
	if ((cur_page = find_page(cur_page, size_m, ptr, &prev)))
		if ((cur = find_ptr(cur_page, size_m, ptr)))
		{
			// Go chercher un nouvel endroit;
			find_new_place();
			cur->use = 0;
			defrag_mem(cur_page, size_m, prev);
			return (cur);
		}
	return NULL;
}

void	*ft_realloc(void *ptr, size_t size)
{
	if (!ptr || size <= 0)
		return (NULL);
	if (g_maloc.tiny && search_and_copy(g_maloc.tiny, TINY_MAP, ptr, size))
		return (NULL);
	else if (g_maloc.small && search_and_copy(g_maloc.small, SMALL_MAP, ptr, size))
		return (NULL);
//	else if (g_maloc.large && search_and_copy_large())
	
}

#include "../inc/malloc.h"

t_maloc		g_maloc = {NULL, NULL, NULL};

void	*alloc_tiny(size)
{
	t_block	*cur;
	
	if (!g_maloc.tiny)
		g_maloc.tiny = mmap(NULL, TINY_MAP, PROT_READ | PROT_WRITE,
			   	MAP_ANON | MAP_PRIVATE, -1, 0);
	cur = (void *)(g_maloc.tiny + sizeof(t_page));
	cur->size = 20;
	printf("%d\n", *(g_maloc.tiny + sizeof(t_page)));
	return g_maloc.tiny + sizeof(t_block);
//	while (cur != g_maloc.tiny + TINY_MAP && cur.free && size < cur.size)
//	{
//		
//	}
}

void	*ft_malloc(size_t size)
{
	if (size <= MAX_TINY)
		return (alloc_tiny(size));
//	else if (size <= MAX_SMALL)
//		alloc_small(size);
//	else
//		alloc_large(size);
	return (NULL);
}

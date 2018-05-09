#include <unistd.h>
#include <stdio.h>
#include "malloc.h"

void	ft_show_alloc()
{
	t_page *tiny;
	t_block	*cur;

	tiny = g_maloc.tiny;
	cur = (void *)(tiny + sizeof(t_page));
	while (1)
	{
		if (cur->size == 0 || cur == (void *)(tiny + TINY_MAP))
		{
			if (!tiny->next)
				break ;
			tiny = tiny->next;
		}
		printf("Size : %d, Use : %d\n", cur->size, (cur->use & (1 << 1)) ? 1 : 0);
		cur = (void*)(cur) + sizeof(t_block) + cur->size;
	}
}

int main(int argc, char **argv)
{
	char *str;
	char *str2;
	char *str3;
	char *str4;
	int i = 0;

	printf("Size of page : %d\n", getpagesize());
	while (i++ < 24)
	{
		str = ft_malloc(300);
		str[0] = 'h';
	}
	ft_show_alloc();
}

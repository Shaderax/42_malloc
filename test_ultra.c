#include "malloc.h"

int main()
{
	char *arrd;
	char *str;

	str = ft_malloc(32);
	ft_free(&arrd);
	ft_free(&arrd);
	ft_free(&arrd);
	str = ft_malloc(32);
	ft_free(&arrd);
	ft_free(&arrd);
	str = ft_calloc(1, 64);
	str = ft_malloc(64);
	str = ft_calloc(1, 64);
	str = ft_malloc(64);
	str = ft_calloc(1, 64);
	str = ft_malloc(64);
	str = ft_calloc(1, 64);
	str = ft_malloc(64);
	str = ft_calloc(1, 64);
	str = ft_malloc(64);
}

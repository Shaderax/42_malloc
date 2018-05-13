#include <unistd.h>
#include <stdio.h>
#include "malloc.h"

int main(int argc, char **argv)
{
	int nb_i = 4;
	char *str[nb_i];

	printf("Size of page : %d\n", getpagesize());
	str[0] = ft_malloc(30);
	str[1] = ft_malloc(30);
	str[2] = ft_malloc(30);
//	str[3] = ft_malloc(30);
	show_alloc();
	// FREE
	ft_free(str[1]);
	show_alloc();
	str[1] = ft_malloc(24);
	


	//
	show_alloc();
}

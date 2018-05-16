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
	str[3] = ft_malloc(30);
	show_alloc();
	ft_strcpy(str[0], "JE SUIS SUISSE!");
	str[0] = ft_realloc(str[0], 20);
	show_alloc();
	str[0] = ft_realloc(str[0], 30);
	show_alloc();
	ft_free(str[0]);
	show_alloc();
}

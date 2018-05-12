#include <unistd.h>
#include <stdio.h>
#include "malloc.h"

int main(int argc, char **argv)
{
	int nb_i = 200;
	char *str[nb_i];
	int i = -1;

	printf("Size of page : %d\n", getpagesize());
	while (++i < nb_i)
		str[i] = ft_malloc(500);
//	str[i] = ft_malloc(30000);
//	str[i] = ft_malloc(300000);
//	str[i] = ft_malloc(0);
	show_alloc();
	i = -1;
	while (i++ < nb_i)
	{
		ft_free(str[i]);
		i++;
		ft_free(str[i]);
		i++;
	}
	printf("\n\n OUI \n\n");
	show_alloc();
	ft_free(str[0]);
}

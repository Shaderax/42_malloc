#include <unistd.h>
#include <stdio.h>
#include "malloc.h"

int main(int argc, char **argv)
{
	char *str;
	char *str2;

	printf("Size of page : %d\n", getpagesize());
	str = ft_malloc(20);
	str[0] = 'h';
	str2 = ft_malloc(20);
	str2[0] = 'o';
	printf("%s\n", str2);
	printf("%s\n", str);
}

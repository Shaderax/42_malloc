#include <unistd.h>
#include <stdio.h>
#include "malloc.h"

int main(int argc, char **argv)
{
	printf("%d\n", getpagesize());
	ft_malloc(1);
}

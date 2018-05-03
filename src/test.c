#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **av)
{
	char *str;
   	str	= malloc(1);

	str[50000000] = 5;
	printf("%c\n", str[0]);
	return (0);
}

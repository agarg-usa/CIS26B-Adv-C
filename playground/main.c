#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char asdf[100];
	puts("Enter a string: ");
	int a = scanf("%100s", asdf);
	printf("%d\n", a);
}
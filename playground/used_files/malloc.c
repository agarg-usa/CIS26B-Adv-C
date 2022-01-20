#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char* arr = malloc(sizeof(char) * 10);
	printf("%d\n", sizeof(arr));
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	unsigned short val = 1024;
	unsigned short key = 127;
	unsigned short result = val ^ key ^ key;

	printf("%hu\n", val & 1);
	printf("%hu\n", 2 || 3);
}
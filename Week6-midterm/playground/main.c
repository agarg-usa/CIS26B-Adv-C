#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char t[] = "XYZabcd9543";
	int n = strcspn(t + 2, "543210");

	printf("%d\n", n);
}
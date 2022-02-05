#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int a = 10;
	int* ptr;
	int ** qtr; // we can also use this as an array of pointers
	ptr = &a;
	qtr = &ptr;
	// qtr points to ptr, and ptr points to a

	printf("%d\n", **qtr);
}

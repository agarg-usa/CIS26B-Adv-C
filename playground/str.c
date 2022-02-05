#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DUMMY_TRAILER '\177'


int main(void)
{
	char *str = "\177";
	printf("%d\n", strcmp("abc", str));
}
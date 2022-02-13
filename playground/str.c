#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define DUMMY_TRAILER '\177'


int main(void)
{
	char s[] = "advanced Perl    ";
	printf("%s\n", strtok(s, "vda"));
	printf("%s\n", strtok(NULL, "vda"));

}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	// char s[] = " advanced C ";
	// printf("%s\n", strtok(s, "\040\ta")); //         a

	char s[] = "	2018	101	A";
	char* pEnd;
	long int n1,n2,n3;
	n1 = strtol(s, &pEnd, 10);
	n2 = strtol(pEnd, &pEnd, 2);
	n3 = strtol(pEnd, &pEnd, 16);
	printf("%ld %ld %ld\n", n1, n2, n3);
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	double ary[] = {2.1, 4.2, 4.5, 9.3, 8.0, 5.7};
	double *ptr = ary + 3;
	ptr++;
	printf("%lf\n", ptr[-2]);
	// ary++;


	// printf("%d\n", sizeof(int)); //4
	// int a = 123;
	// int *ptr = &a;
	// printf("%p\n", ptr); //123
	// printf("%p\n", ptr+1); //123

	// int arr[6] = {1,2,3,4,5,6};
	// ptr = arr;
	// int *newPtr = arr + 3;
	// printf("%d\n", newPtr - ptr);

}
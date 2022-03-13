#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cmpfunc(const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
   // note that the type of the cmpfunc that qsort will call will be of the pointer
   // to the data of what you give
   // so you pass in a list of ints, it will call the compare function with pointers to those ints
}

int main(void)
{
	int values[] = {123, 45, 234, 1, -5};
	for(int i = 0; i < 5; i++) {
		printf("%d ", values[i]);
	}
	printf("\n");

	qsort(values, 5, sizeof(int), cmpfunc); // this is the std qsort function
	// there is also a bsearch function

	for(int i = 0; i < 5; i++) {
		printf("%d ", values[i]);
	}
}
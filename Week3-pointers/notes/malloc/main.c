#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MEM_ERROR printf("Memory allocation error\n"); exit(1);

int main(void)
{
	double *mallocPtr;
	mallocPtr = (double *)malloc(sizeof(double)); // allocates memory on the heap for a double
	if (mallocPtr == NULL)
	{
		MEM_ERROR;
	}

	printf("%f\n", *(mallocPtr)); //prints garbage data
	*mallocPtr = 123;
	printf("%f\n", *mallocPtr);

	double* callocPtr;
	callocPtr = (double *)calloc(1, sizeof(double)); // allocates memory on the heap for a double, initializes all data to 0
	//calloc can be used to initalize a contigous set of memory to 0, can be used for arrays
	//for example callocArr = (double *)calloc(10, sizeof(double)); is a 10 element array of doubles
	//you can also use malloc: callocPtr = (double *)malloc(10*sizeof(double));

	if (callocPtr == NULL)
	{
		MEM_ERROR;
	}

	double* arrDoublePtr;
	arrDoublePtr = (double *)calloc(10, sizeof(double));
	double* temp;
	temp = (double*)realloc(arrDoublePtr, 20 * sizeof(double)); //tries to change array size from 10 to 20
	// tries to extend current array in place, if not possible then it will move all elemeents to a new place in the heap
	if(temp == NULL)
	{
		MEM_ERROR;
	}
	else
	{
		arrDoublePtr = temp;
	}

	free(mallocPtr); // frees memory on the heap
	//make sure to not free stack variables, or else you will get a segfault

	free(arrDoublePtr);
	//the WHOLE array of arrDoublePtr will be free'd by doing this
	// sizeof(arrDoublePtr) is 20*sizeof(double), not just sizeof(double)
	// NOTE: this is because the array was defined in this scope. if you pass in this pointer to a function it the sizeof() method will return just sizeof(double)
	// this is why you need to also pass in the size of the array in all std functions

	




}
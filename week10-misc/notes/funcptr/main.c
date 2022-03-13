#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned int myHashFn(const char* key, int size);

int main(void)
{
	printf("Address of myHashFn: %p\n", myHashFn); // our function has a pointer to it

	unsigned int (*hashFnPtr)(const char*, int) = myHashFn; // how we define a function pointer (Pre-ansi syntax)
	// can be used to pass around

	unsigned int (*fnPtrArr[4])(const char*, int); // array of function pointers
	unsigned int (**iter)(const char*, int); // array of pointers to pointers
	iter = fnPtrArr; // assign the array of pointers to the array of pointers

	// you can also return function pointers
	// it is reccomended to use typedef to define the function pointer declerations

	// pointer datatypes can start to get complicated, use the right -> left rule
	// * pointer
	// [] array
	// () function

	// int (*f)(int); f is a pointer to a funcction with param int and return type int
	// int (*f[6])(int); f is an array of pointers to functions with param int and return type int
	// int (*myTablePtr)[2][MAX_COL] myTablePtr is a pointer to a 2d array of ints
	

}

unsigned int myHashFn(const char* key, int size)
{
	unsigned int hash = 0;
	int i = 0;
	while (key[i] != '\0')
	{
		hash = hash * 31 + key[i];
		i++;
	}
	return hash % size;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int a[6] = {1,2,3,4,5,6};
	int* ptr;
	ptr = &a[3]; // you could also just write a + 3
	printf("%d\n", *ptr); //4
	printf("%d\n", *(ptr-1)); //3
	printf("%d\n", ptr[1]); //5

	int ptrDistance = ptr - a;
	printf("%d\n", ptrDistance); //3

	//pointer + constant / pointer - constant gives a new pointer to that many places shifted
	// +, -, ++, --,  +=, -= all work
	// pointer - pointer gives distance
	// pointer + pointer is an error

	int* pWalk = a;
	while(pWalk < ptr) //you can use relational operators on pointers of the same type
	{
		printf("%p\n", pWalk);
		pWalk++;
	}

	//the last element will always be the first elem pointer + the size - 1
	int* lastPtr = a + sizeof(a)/sizeof(int) - 1;

	int copyOfA[6];
	memcpy(copyOfA, a, sizeof(a)); //copies the array a into copyOfA
	//could have also did 6*sizeof(int)

	memcmp(a, copyOfA, sizeof(a)); //compares the two arrays
	//similar to strcmp but does not stop for \0
	




}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int a = 5;
	printf("%d\n", a);
	int* ptr;
	ptr = &a;

	printf("%d\n", *ptr); //prints value of a
	printf("%p\n", ptr); //prints pointer of a
	printf("%p\n", &ptr); //prints pointer of ptr

	int b;
	printf("%p\n", &b); //prints pointer of b
	printf("%d\n", b); //prints value of b
	// since b is uninitialized it has garbage data
	b = 5;
	ptr = &b;

	void* garabgePointer; // just a pointer, unknown to what type (void type)
	printf("%p\n", garabgePointer); //prints to a random pointer

	// char* strPtr; // pointer to a string
	// printf("garbage string: %s\n", strPtr); // prints garbage data


}

// void swap(int a, int b); passes by value, incorrect
//void swap(int& a, int& b)  incorrect, C does not have references

void swap(int* a, int* b) //pass by reference
{
	int temp = a;
	a = b;
	b = temp;
}

//DO NOT DO THIS
char* getFileName()
{
	char* name;
	printf("Enter file name: ");
	scanf("%s", name);
	return name;
	//THIS IS INCORRECT
	// name is a stack variable, so it will be destroyed when the function ends
	// do not return pointers to stack variables in functions
}
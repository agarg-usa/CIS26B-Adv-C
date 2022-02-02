#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char myStr[20] = "Hello";
	printf("%ld\n", strlen(myStr)); //5
	// strlen goes till it finds a \0

	char* myStrConcat = myStr + 1;
	// myStrConcat is now "ello"

	strcpy(myStrConcat, "World");
	// myStrConcat is now "World"
	// myStr is HWorld

	char* myStr2 = "orlasdf";
	//printf("%s\n", myStr+2); //orld
	printf("%d\n", strncmp(myStr+2, myStr2, 2)); //prints 0 since the two strings are the same


	strcpy(myStr, "Hello");
	char* myPtr = strchr(myStr, 'l'); // points to first l
	// strrchr does same but searches from reverse (last l)
	// return NULL if not found

	//you can find 2nd l by adding 1 to myPtr

	strcpy(myStr, "Hello World");
	myPtr = strstr(myStr, "World"); // points to W

	char* digits = "1234567890";
	strcpy(myStr, "1234f");
	int a = strspn(myStr, digits);
	// returns index of first char not in set
	// in this case returns 4
	// if all chars in set, returns strlen(myStr)

	// strcspn does the opposite, returns index of first char in set
	//slide 42



}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

char* getName();

// argc tells you the number of arguments passed to the program
// argv is an array of strings
int main(int argc, char *argv[])
{
	char myStr[100] = "Hello";
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
	int myIndex = strspn(myStr, digits);
	// returns index of first char not in set
	// in this case returns 4
	// if all chars in set, returns strlen(myStr)

	// strcspn does the opposite, returns index of first char in set
		// strpbrk does the same but returns a pointer to the first char in set instead of the index


	printf("%.*s\n", 3, myStr); // prints 123
	// %.*s allows you to input a variable num for the number of chars to print


	char* delimiters = " ,.?!:;\t\n"; // delimiters to use
	strcpy(myStr, "Hello, World!\nMy Name Is");

	char* myStringPointers = strtok(myStr, delimiters); // strtok will split the string into tokens
	// WARNING it does modify the original string to include \0.
	// so after the first call, myStr3 will be "Hello\0"

	while(myStringPointers != NULL)
	{
		printf("%s\n", myStringPointers);
		myStringPointers = strtok(NULL, delimiters); // putting NULL in the first arg will start from the last token that strtok searched through
		// prints Hello\nWorld\nMy\nName\nIs\n
	}

	printf("\n%s\n\n", myStr); // prints Hello\0 since strtok modified myStr


	strcpy(myStr, "23456");
	long num;
	// one way to convert this num is to use sscanf like
	// if(sscanf(myStr, "%ld", &num) == 1)

	// another way is to use strtol
	errno = 0; // included from <errno.h>
	char* endPtr;
	num = strtol(myStr, &endPtr, 10); // 10 is base

	if(*endPtr == '\0') // if endPtr is \0, then the entire string was converted
	{
		printf("%ld\n", num);
	}
	else
	{
		printf("Not a number!");
	}

	if(errno == ERANGE)
	{
		printf("Overflow!\n");
	}

	// similar methods to strtol exist for strtod (double), strtoul (unsigned long)

	char* name;
	name = getName();
	printf("%s\n", name);
	// getName();
	// printf("%s\n", name); // example of name getting overwritten
	// // to prevent this you can use strcpy


	char *list[5] = {"Hello", "World", "Today", "Now", "Season"};
	int len = 5;

	char** listPtr = list + 3; // points to Now

	puts(*listPtr); // prints Now
	puts(listPtr[-1]); // prints Today
	listPtr--;
	char** listPtrB = listPtr - 1;

	// strcpy(*listPtr, *listPtrB); WARNING This will NOT WORK
	// this will cause a segfault. This is because listPtr points to a string literal,
	// and you can not overwrite a string literal.

	// instead the way to achieve this is to make a new string and put it in the list

	char* temp = (char*) malloc(strlen(*listPtrB) + 1); //allocates memory length of listPtrB + 1 character more for \0
	strcpy(temp, *listPtrB); // copies listPtrB into temp
	*listPtr = temp; // points listPtr to temp

	puts("");
	for(int i = 0; i < len; i++)
	{
		printf("%s\n", list[i]);
	}
	// list is now hello world world now season
}

char* getName()
{
	// char s[32]; // incorrect, you cant return this because its a local var
	static char s[32]; // static means it will be stored in memory for the duration of the program

	// warning: using static compared to malloc will mean that if the caller function directly says
	// var1 = getName() -> var1 = s
	// and if getName() is called again, overwriting s, then var1 will indirectly also get overwritten

	puts("Enter name:");
	fgets(s, sizeof(s), stdin);

	return s;
}
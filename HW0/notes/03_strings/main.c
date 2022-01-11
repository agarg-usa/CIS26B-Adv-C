#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FLUSH while(getchar() != '\n');
int main(void)
{
	//a string is a sequence of characters treated as a unit
	//C string is an array of characters ending with null character ('\0')

	char charArrExample[6] = {'B', 'e', 'n', '\0'}; //rest of the array is filled with null characters
	//char charArrExample2[3] = "Ben"; //incorrect, we need a size of 4 so we can have a \0
	char charArrExample2[4] = "Ben";
	char charArrExample3[] = "Ben";
	char* charPointerExample = "Ben";

	printf("%s\n", charArrExample);
	printf("%s\n", charArrExample2);
	printf("%s\n", charArrExample3);
	printf("%s\n", charPointerExample);

	printf("%ld\n", sizeof(charArrExample)); //6 bytes long, B e n \0 \0 \0
	printf("%ld\n", sizeof(charArrExample2)); // 4 bytes long, B e n \0
	printf("%ld\n", sizeof(charArrExample3)); // 4 bytes long, B e n \0
	printf("%ld\n", sizeof(charPointerExample)); //8 bytes long (pointers are 64bit for 64bit computers)

	// "A" = A \0
	// 'a' = a
	// "" = \0
	// '' = not valid

	char nameInput[21]; //20 characters long
	printf("Enter your name: ");
	scanf("%20s", nameInput); //nameInput[] is already a pointer, so DO NOT DO &nameInput
	//always put the length of the string (ex. 20 in %20s) to prevent buffer overflow

	//After reading in a string, you have to flush the buffer
	//while(getchar() != '\n'); // flushes buffer

	//if you use #define FLUSH in the beginning of the file you can also just do this
	FLUSH;

	//you can also use regex when reading

	//scanf("%20s", nameInput); if you enter John Doe, nameInput will only be John
	scanf("%20[^\n]", nameInput); //if you enter John Doe, nameInput will be John Doe
	FLUSH;

	char numberInput[5];
	//you can also do this with numbers
	scanf("%5[012345]", numberInput); //once a character which isnt 0 1 2 3 4 or 5 is entered, input stops
	FLUSH;

	puts("This string was printed by puts, which is similar to printf but it adds a newline");
	fprintf("fprintf lets you put strings but for generic files / streams" , stdout);

	char victorName[10] = "Victor";
	sizeof(victorName); // returns 10, length of arr
	strlen(victorName); // returns 6, length of string / first time the null character appears

	char nameToCopyTo[10];
	// if we want to copy victorName into nameToCopyTo, we need to use strcpy
	//nameToCopyTo = victorName; //this is just a shallow copy (since they are both pointers)

	strcpy(nameToCopyTo, victorName); //this is a deep copy (since they are different pointers)

	char copyFirstChars[5];
	strncpy(copyFirstChars, victorName, 4); //copies first 4 characters of victorName into copyFirstChars
	copyFirstChars[4] = '\0'; //you have to manually add the null character to the end of the string
	//becomes Vict

	strncpy(copyFirstChars, victorName+1, 4);
	copyFirstChars[4] = '\0';
	//becomes icto

	if(strcmp("a", "b") == 0) //returns 0 if they are equal
	{
		printf("a and b are equal\n");
	}
	else if(strcmp("a", "b") > 0)
	{
		printf("a is greater than b\n");
	}
	else
	{
		//prints this statement since b (ascii value) is greater than a
		//opposite of alphabetical
		printf("a is less than b\n");
	}


	char vicOver[10] = "Vic";
	char torOver[10] = "tor";

	strcat(vicOver, torOver); //vicOver = vicOver + torOver
	//vicOver becomes Victor

	char* wikipedia = "Wikipedia";
	char* pointerToI = strchr(wikipedia, 'i'); //returns a pointer to the first occurrence of 'i' in wikipedia
	//if it doesnt find it, it returns NULL
	pointerToI = strchr(pointerToI+1, 'i'); //returns a pointer to the second occurrence of 'i' in wikipedia
	// strrchr searches in reverse dir

	//sscanf reads from a string and can parse out details
	//sprintf writes to a string and can combine variables into a string


}
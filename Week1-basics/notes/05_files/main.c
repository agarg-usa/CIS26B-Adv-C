#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	FILE* fpData; //file pointer
	fpData = fopen("data.txt", "r"); //r , w , a
	//opens the file
	if (fpData == NULL)
	{
		// this can mean that data.txt does not exist
		printf("Error opening file\n");
		exit(1);
	}

	// int closeCheck = fclose(fpData);
	// //after you are done with the file you have to close it

	// if (closeCheck == EOF) //checks if file is closed or not properly
	// {
	// 	printf("Error closing file\n");
	// 	exit(1);
	// }

	//other important file functions
	//rewind() moves file pointer to beginning
	// rename() changes the name of the file
	// remove() deletes the file

	//getchar() takes in one char from keyboard
	// putchar() prints out one char (returns EOF is error)

	//the reason c is an int is so that it can work with 8 bytes, letting it have EOF and error bits
	int c = getc(fpData); //reads one char from file
	putc(c, stdout); //prints out one char
	puts("");
	//synonyms are fputc and fgetc

	FILE* fpDataOut = fopen("dataOut.txt", "w");
	fputc(c, fpDataOut);

	ungetc('A', fpData); //puts char back into file stream


	// these are all for reading in characters, but below you can use fscanf and fprintf for reading and writing whole strings / data

	int year = 1233;
	double price = 34.23;

	fprintf(fpDataOut, "\n%d %.2f\n", year, price);

	char fileContents[4];
	fscanf(fpData, "%3s", fileContents);
	fileContents[3] = '\0';
	puts(fileContents);

	//scanf tricks
	// if we want to read 12/24/21
	// we can do
	// scanf("%d/%d/%d", &month, &day, &year);
	// or scanf("%d %*c %d %*c %d", &month, &day, &year);
	// putting the space also disregards all white space (even if its multiple spaces, so it will read 12   / 23/21)

	//if we want to read file to EOF

	char content;
	while(fscanf(fpData, "%c", &content) != EOF)
	{
		printf("%c", content);
	}
}
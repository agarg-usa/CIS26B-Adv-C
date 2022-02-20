#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {} RECORD;

int main(void)
{
	FILE *fp;
    long int p;
    char c;

    fp = fopen("test.dat", "w+b");
    for (c = 'A'; c < 'G'; c++)
    {
        fwrite(&c, sizeof(char), 1, fp);
    }
	// writes ABCDEF to file

    p = ftell(fp); // returns 6, current pos in file
    p--; // p = 5
    p--; // p = 4
    fseek(fp, p, SEEK_SET); // goes to index 4 of file (5th element)
	/*
		A B C D E F
		0 1 2 3 4 5
		        ^
				p
	*/
    fread(&c, sizeof(char), 1, fp); // reads in that 4th character (E)
    printf ("%c\n", c); // prints E
}

/*

	char mode[] = "wb";
	char fileName[] = "Payroll";
	RECORD pay;
	RECORD *list = (RECORD *)malloc(10 * sizeof(RECORD));
	FILE *fp;
	fp = fopen(fileName, mode);
	//fread(pay, sizeof(pay), 1, fp); error, need to pass pointer in
	fread(&pay, sizeof(pay), 1, fp);
	//fread(list, sizeof(list), 25, fp); error, list only has space for 10 elements
	fread(list, sizeof(list), 10, fp);
	fclose(fp);
	// error, make sure to free list
	free(list);
*/

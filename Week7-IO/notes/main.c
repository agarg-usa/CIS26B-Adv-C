#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FILE_NAME "test.bin"

struct record{
	char key[50];
	int num;
};

int main(void)
{
	FILE* fp;
	double x = 95617.21;
	fp = fopen(FILE_NAME, "w");
	// fprintf(fp, "%lf", x);
	// if you use fscanf / fprintf, you are going to be dealing with strings
	// this means that it is possible (like in this case) where x != y, but there
	// string representations are the same
	// fix this by writing in binary files
	if(fwrite(&x, sizeof(double), 1, fp) < 1)
	{
		printf("error writing to file\n");
		exit(1);
	}

	fclose(fp);

	double y;
	fp = fopen(FILE_NAME, "r");
	// fscanf(fp, "%lf", &y);
	if(fread(&y, sizeof(double), 1, fp) < 1)
	{
		printf("error reading from file\n");
		exit(1);
	}
	printf("%lf\n", y);
	// fclose(fp);

	if(x == y)
	{
		printf("x and y are the same\n");
	}
	else
	{
		printf("x and y are not the same\n");
	}

	// rewind(fp); // rewinds file pointer to the beginning of the file
	// rename("test.txt", "test2.txt"); // renames file
	// remove("test.txt"); // deletes file

	printf("Currently %ld bytes in file\n", ftell(fp));

	rewind(fp);
	fseek(fp, 1*sizeof(char), SEEK_SET);
	// SEEK_SET = beginning of file
	// SEEK_CUR = current position
	// SEEK_END = end of file

	fclose(fp);
	fp = fopen(FILE_NAME, "w+b");
	// rb / wb / ab = read / write / append in binary
	// r+b read and write in an existing binary file
	// w+b read/write in a new bin file
	// a+b = read and append in existing bin file

	struct record table[100] = {""}; // hash table (all 0 bytes)

	// writes hash table to file
	// fwrite(table, sizeof(struct record), 100, fp);

	strcpy(table[0].key, "hello");
	table[0].num = 1;
	fwrite(table, sizeof(struct record), 1, fp);

	// searching from a hashtable on disk

	int address = 2; // = hash(key)
	fseek(fp, address*sizeof(struct record), SEEK_SET);
	fread(&table[address], sizeof(struct record), 1, fp);

	//this does not deal with collisions.
	// possible collision resolution: linear probe
	// buckets with fixed size
	fclose(fp);


	// weird printf quirks
	printf("%+d\n", 123); // +123
	printf("%0d\n", 123); // 00123
	printf("%o\n", 123); // 173 octal (base 8)
	printf("%x\n", 123); // 7b hexadecimal (base 16)
	// remember * is a wildcard, so you have to input the variable that * means in printf

	char myFormattedString[20];
	sprintf(myFormattedString, "My Num: %d", 123);
	puts(myFormattedString);

}
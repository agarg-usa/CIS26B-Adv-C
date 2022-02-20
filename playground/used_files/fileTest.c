#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	FILE* fp = fopen("test.txt", "r+b");

	char c = fgetc(fp);
	printf("%c\n", c);
	rewind(fp);
	char otherChar = 'b';
	fwrite(&otherChar, sizeof(char), 1, fp);
	rewind(fp);
	c = fgetc(fp);
	printf("%c\n", c);
	fclose(fp);
	return 0;
}
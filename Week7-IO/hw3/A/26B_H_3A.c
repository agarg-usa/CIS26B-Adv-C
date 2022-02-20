/*

 Binary Files

 There are a number of errors (about 6) in the following program.
 Locate all errors, fix them (as shown below), run the program and save its output.

 Here is an example:

 FILE fp; // <== Error: Comment the line and write the correct line below

 // FILE fp; // Error #1
 FILE *fp;

 NAME: Aryan Garg
 IDE: Vscode / Gcc
 */
#include <stdio.h>
#include <stdlib.h>  // exit
#include <string.h>
#include <ctype.h>

#define FILENAME "out.dat"

#define SHOW_RECORDS(x) rewind(fp); \
fread(temp, sizeof(RECORD), x, fp); \
for (k = 0; k < x; k++ ) printf("%s  %s\n", temp[k].id, temp[k].name); \
rewind(fp);

typedef struct
{
    // char name[32];
    // char id[4];
	// 2 errors, one is that the id should be first and the name should be second because that is how it was defined
	// second is that is should be length of 5 because of \0 char
	char id[5];
	char name[32];
} RECORD;

int main(void)
{
    FILE *fp;
    RECORD list[5] = {{"1111", "Alpha"}, {"2222", "Beta"}, {"3333", "Gamma"}, {"4444", "Delta"}, {"5555","Epsilon"}};
    RECORD myList[3] = {{"7777", "Eta"}, {"8888", "Theta"}, {"9999", "Iota"}};
    //RECORD temp[5], item = {"6666", "Zeta"}, newItem; error the temp buffer needs to be bigger
	RECORD temp[100], item = {"6666", "Zeta"}, newItem;
    long pos, cnt;
    int k, n = 5;


    if ((fp = fopen(FILENAME, "w+b")) == NULL)
    {
        printf("Could not open %s.\n", FILENAME);
        exit(1);
    }
    fwrite(list, 5, sizeof(RECORD), fp); // error but technically works
    SHOW_RECORDS(5);

    // calculate the number of records in the file
    fseek(fp, 0, SEEK_END);
    pos = ftell(fp);
    printf("\nThere are %ld records in this file.\n", pos/sizeof(RECORD) );

    // append one item
    fseek(fp, 0, SEEK_END);
    // fwrite(item, sizeof(RECORD), 1, fp); error need to pass in the pointer to item
	fwrite(&item, sizeof(RECORD), 1, fp);

    // calculate the number of records in the file
    fseek(fp, 0, SEEK_END);
    pos = ftell(fp);
    printf("\nNow there are %ld records in this file.\n", pos/sizeof(RECORD) );

    // Display the last record
    fseek(fp, -1 * sizeof(RECORD), SEEK_END);
    fread(&newItem, sizeof(RECORD), 1, fp);
    printf("\nLast item is %s.\n", newItem.name);

    // append myList
    fseek(fp, 0, SEEK_END);
    fwrite(myList, sizeof(RECORD), 3, fp);

    // calculate the number of records in the file
    fseek(fp, 0, SEEK_END);
    pos = ftell(fp);
    //cnt =  pos/sizeof("RECORD"); error its sizeof(RECORD) not sizeof("RECORD")
	cnt =  pos/sizeof(RECORD);
    printf("\n\nThere are %ld records in this file.\n", cnt );
    SHOW_RECORDS(cnt);

    // replace the n-th element by {"0000", "ZERO"} // newItem
    fseek(fp, n * sizeof(RECORD), SEEK_SET); //
    strcpy(item.id, "0000");
    strcpy(item.name, "ZERO");
    fwrite(&item, sizeof(RECORD), 1, fp);
    fseek(fp, -1 * sizeof(RECORD), SEEK_END);
    fread(&newItem, sizeof(RECORD), 1, fp);
    printf("\n\nThe %d-th record has changed: %s %s.\n", n, newItem.id, newItem.name);
    SHOW_RECORDS(cnt);

    fclose(fp);

    return 0;
}

/*	================= Sample Output ================= */
/*	Results:


1111  Alpha
2222  Beta
3333  Gamma
4444  Delta
5555  Epsilon

There are 5 records in this file.

Now there are 6 records in this file.

Last item is Zeta.


There are 9 records in this file.
1111  Alpha
2222  Beta
3333  Gamma
4444  Delta
5555  Epsilon
6666  Zeta
7777  Eta
8888  Theta
9999  Iota


The 5-th record has changed: 9999 Iota.
1111  Alpha
2222  Beta
3333  Gamma
4444  Delta
5555  Epsilon
0000  ZERO
7777  Eta
8888  Theta
9999  Iota
 */

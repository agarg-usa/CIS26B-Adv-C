#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_COL 5

int main(void)
{
	int table[2][5] = {
		{1, 2, 3, 4, 5},
		{6, 7, 8, 9, 10}
	};


	printf("%d\n", table[1][1]);
	// printf("%d\n", table[6]); this doesnt work, table[] returns an int []

	int (*myTablePtr)[2][MAX_COL] = &table; // this is a pointer to a matrix of ints
	printf("%d\n", (*myTablePtr)[1][1]);

}

void printTable(int table[][MAX_COL], int rows, int cols) // only the size of last elem in the table[][] definition is needed
// this is because int is really an int**, and this tells the compiler how much to push the stack pointer down.
{

}
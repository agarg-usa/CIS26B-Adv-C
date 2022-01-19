/*
 CIS 26B: Homework 1B
 ********************
 NAME:
 IDE (compiler):
 *************************************************************************
	Arrays, Strings, Structures, Pointers, Functions and Files
	This program provides information about two-tear colleges in California.

 Suggested Design #1
 main calls the following functions:
   - readFile
   - insertionSort
   - printRange
   - writeFile

 Suggested Design #2
 main calls the following functions:
   - readFile
   - insertionSort
   - printManager calls the following functions in a loop
		- getRange
		- printRange
   - writeFile

 Design #3 - your design
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 64
#define INPUT_SIZE 100
#define FLUSH while (getchar() != '\n')

typedef struct
{
	int rank;
	char name[NAME_SIZE];
	int year;
	int numStud;
} COLLEGE;

void readFile(const char inFileName[], COLLEGE list[], int *count);
void insertionSort(COLLEGE list[], int count);
void printRange(const COLLEGE list[], int count);
void writeFile(const char outFileName[], const COLLEGE list[], int count);

int main(void)
{
	COLLEGE collegeData[INPUT_SIZE];
	char inFileName[NAME_SIZE] = "in.txt";
	char outFileName[NAME_SIZE] = "out.txt";
	int count; // actual number of colleges

	printf("Enter input file (0 for default): ");
	scanf("%64s", inFileName);
	if (inFileName[0] == '\0' || inFileName[0] == '0')
	{
		strcpy(inFileName, "in.txt");
	}

	FLUSH;

	printf("Enter output file (0 for default): ");
	scanf("%64s", outFileName);
	if (outFileName[0] == '\0' || outFileName[0] == '0')
	{
		strcpy(outFileName, "out.txt");
	}

	FLUSH;

	readFile(inFileName, collegeData, &count);
	insertionSort(collegeData, count);

	while(1)
	{
		int start, end;
		printf("Enter range (0 0 to quit): ");
		scanf("%d %d", &start, &end);
		if(start == 0 && end == 0)
		{
			break;
		}
		start = start - 1;
		if (start < 0 || start >= count || start + end > count)
		{
			printf("invalid input\n");
			FLUSH;
			continue;
		}

		printRange(collegeData + start, end);
	}

	writeFile(outFileName, collegeData, count);
	return 0;
}

void readFile(const char inFileName[], COLLEGE list[], int *count)
{
	FILE *fp;
	fp = fopen(inFileName, "r");
	if (fp == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}

	int rank, year, numStud;
	char name[NAME_SIZE] = "";

	int i;
	for (i = 0; i < INPUT_SIZE && fscanf(fp, "%d", &rank) != EOF; i++)
	{
		COLLEGE myCol;
		myCol.rank = rank;
		int j;
		fgetc(fp); // skip space
		for (j = 0; j < NAME_SIZE; j++)
		{
			name[j] = fgetc(fp);
			if (name[j] == ';')
			{
				break;
			}
		}
		name[j] = '\0';
		strcpy(myCol.name, name);
		fscanf(fp, "%d %d", &year, &numStud);
		myCol.year = year;
		myCol.numStud = numStud;
		list[i] = myCol;
	}

	*(count) = i;
	fclose(fp);
}

void insertionSort(COLLEGE list[], int count)
{
	COLLEGE temp;
	COLLEGE *pCurr, *pLast;
	pLast = list + count - 1;
	COLLEGE *pWalk;

	for (pCurr = list + 1; pCurr <= pLast; pCurr++)
	{
		temp = *pCurr;
		pWalk = pCurr - 1;
		while (pWalk >= list && temp.rank < pWalk->rank)
		{
			*(pWalk + 1) = *pWalk;
			pWalk--;
		}
		*(pWalk + 1) = temp;
	}
}

void printRange(const COLLEGE list[], int count)
{
	for (int i = 0; i < count; i++)
	{
		printf("%d %s; %d %d\n", list[i].rank, list[i].name, list[i].year, list[i].numStud);
	}
}

void writeFile(const char outFileName[], const COLLEGE list[], int count)
{
	FILE* fp;
	fp = fopen(outFileName, "w");

	for (int i = 0; i < count; i++)
	{
		fprintf(fp, "%d %s; %d %d\n", list[i].rank, list[i].name, list[i].year, list[i].numStud);
	}
	fclose(fp);
}
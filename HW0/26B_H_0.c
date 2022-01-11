/*
 CIS 26B: Homework 0
 ********************
 NAME: Aryan Garg
 IDE(compiler): Gcc / Vscode
 *********************************************************************************************
 This program determines the winners at a particular talent competition.

 Your task:

 1. Code review: read and understand this program
 2. Call the following functions in main:
		calculateScore
		insertionSort
		writeFile
		displayWinners
 3. Call getMinMax in calculateScore
 4. Define and call the displayWinners function
 5. Run the program.
 6. Save its output at the end of the source file as a comment.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_JUDGES 5
#define NUM_PERFRM 100
#define NAME_SIZE 32

typedef struct
{
	char name[NAME_SIZE];
	int scores[NUM_JUDGES];
	int final;
} PERFORMER;

typedef struct
{
	int size;					// the actual number of performers
	PERFORMER list[NUM_PERFRM]; // the array of performers

} LIST;

void printInfo(void);
void printEnd(void);

int readPerfData(LIST *perfData, char fileName[]);
int getOutFileName(const char fileName[], char outFileName[]);
void writeFile(const LIST *perfData, char outFileName[]);
void calculateScore(LIST *perfData);
void getMinMax(const int scoreList[], int *min, int *max);
void insertionSort(LIST *perfData);
void displayWinners(const LIST *perfData);
void showErrorMessage(int errorCode, char s[]);

int main(void)
{
	char inFileName[][NAME_SIZE] =
		{"performers.txt", "contestants.txt", "abc.txt", "test", "test.txt", ""};
	LIST perfData;
	int i, success;
	char outFileName[32];

	// call printInfo
	printInfo();
	for (i = 0; *(inFileName[i]) != '\0'; i++)
	{
		if (!getOutFileName(inFileName[i], outFileName))
			showErrorMessage(0, inFileName[i]);
		else
		{
			success = readPerfData(&perfData, inFileName[i]);
			if (success != 1)
				showErrorMessage(success, inFileName[i]);
			else // everything is OK
			{
				printf("Reading from \"%s\" . . . \nWriting to \"%s\"\n\n", inFileName[i], outFileName);
				// call calculateScore
				calculateScore(&perfData);

				// call insertionSort
				insertionSort(&perfData);

				// call writeFile
				writeFile(&perfData, outFileName);

				// call displayWinners
				displayWinners(&perfData);
			}
		}
	}
	// call printEnd
	printEnd();

	return 0;
}
/* *******************************************************
  Displays the winner(s)
PRE  : perfData
POST : one or more winners displayed
*/
void displayWinners(const LIST *perfData)
{
	int maxScore = 0;

	for (int i = 0; i < perfData->size; i++)
	{
		if (perfData->list[i].final > maxScore)
		{
			maxScore = perfData->list[i].final;
		}
	}

	puts("The winners of the competition are:");
	for (int i = 0; i < perfData->size; i++)
	{
		if (perfData->list[i].final == maxScore)
		{
			printf("\t%s with a score of %d\n", perfData->list[i].name, perfData->list[i].final);
		}
	}
	puts("");

}

/* *******************************************************
	Prints information about the project.
 PRE  : nothing
 POST : info printed
 */
void printInfo(void)
{
	printf("\n\n\t\tArrays, Strings, Structures, Sorting, Pointers, and "
		   "\n\n\t\t\t\tDynamic Allocation of Memory\n\n");
	printf("This program determines the winners at a particular talent competition.\n");
	putchar('\n');
}

/* *******************************************************
	Prints a farewell message.
 PRE  : nothing.
 POST : farewell message printed
 */
void printEnd(void)
{
	printf("\n\t\tThank you for using the program,"
		   "\n\t\tHave a great day!\n");
}

/* *******************************************************
   Reads data from the input file into an array of structures
PRE  : perfData - pointer to an empty structure
	   fileName - the name of the input file
POST : perfData - filled with data from the input file
*/
int readPerfData(LIST *perfData, char fileName[])
{
	int success = 1;
	int num, i, j;
	FILE *fpIn;

	fpIn = fopen(fileName, "r");
	if (!fpIn)
	{
		success = -2; // file not found
	}
	else
	{
		fscanf(fpIn, "%d", &num);
		if (num > NUM_PERFRM)
		{
			success = -1; // file too big
		}
		else
		{
			perfData->size = num;
			for (i = 0; i < num; i++)
			{
				fscanf(fpIn, "%s", perfData->list[i].name);
				for (j = 0; j < NUM_JUDGES; j++)
					fscanf(fpIn, "%d", &(perfData->list[i].scores[j]));
			}
			fclose(fpIn);
		}
	}

	return success;
}
/* *******************************************************
   Generates the output file's name from the inputFile's name
			 "test.txt" => "test_out.txt"
PRE  : fileName - input file name
POST : outFileName - output file name
*/
int getOutFileName(const char fileName[], char outFileName[])
{
	char temp[NAME_SIZE];
	char *ptr;
	int valid = 1;

	strcpy(temp, fileName);
	ptr = strchr(temp, '.');
	if (ptr)
	{
		*ptr = '\0';
		strcpy(outFileName, temp);
		strcat(outFileName, "_out.txt");
	}
	else
		valid = 0; // invalid file name: it does not contain '.'

	return valid;
}

/* *******************************************************
   Writes the array to an output file.
PRE  : perfData
	  outFileName
POST : output file contains data
*/
void writeFile(const LIST *perfData, char outFileName[])
{
	FILE *fpOut;
	int i, j;

	fpOut = fopen(outFileName, "w");
	fprintf(fpOut, "%d\n", perfData->size);
	for (i = 0; i < perfData->size; i++)
	{
		fprintf(fpOut, "%-20s ", perfData->list[i].name);
		for (j = 0; j < NUM_JUDGES; j++)
			fprintf(fpOut, "%4d", perfData->list[i].scores[j]);
		fprintf(fpOut, "  %4d\n", perfData->list[i].final);
	}
	fclose(fpOut);
}

/* *******************************************************
   Determines the lowest and highest score for one performer
PRE  : scoresList[] - a list of 5 scores
POST : lowest, highest scores determined
	  and passed back to the caller as output parameters
*/
void getMinMax(const int scoreList[], int *min, int *max)
{
	int j;

	*min = *max = scoreList[0];
	for (j = 1; j < NUM_JUDGES; j++)
	{
		if (scoreList[j] < *min)
			*min = scoreList[j];
		if (scoreList[j] > *max)
			*max = scoreList[j];
	}
}

/* *******************************************************
   Calculates the final score for each performer:
   average of 3 scores with lowest and highest eliminated
PRE  : perfData - without the final score
POST : perfData - with the final score calculated
*/
void calculateScore(LIST *perfData)
{
	int i, j;
	int finalScore, lowest, highest;

	for (i = 0; i < perfData->size; i++)
	{
		finalScore = 0;
		for (j = 0; j < NUM_JUDGES; j++)
		{
			finalScore += perfData->list[i].scores[j];
		}
		// call getMinMax
		getMinMax(perfData->list[i].scores, &lowest, &highest);

		perfData->list[i].final = finalScore - lowest - highest;
	}
}
/* *******************************************************
   Sorts the array in descending order by the final score
PRE  : perfData - has data, including final score
POST : perfData - sorted
*/
void insertionSort(LIST *perfData)
{
	int curr, walk;

	for (curr = 1; curr < perfData->size; curr++)
	{
		PERFORMER temp = perfData->list[curr];
		walk = curr - 1;
		while (walk >= 0 && temp.final > perfData->list[walk].final)
		{
			perfData->list[walk + 1] = perfData->list[walk];
			walk--;
		}
		perfData->list[walk + 1] = temp;
	}
}
/* *******************************************************
  Displays the error message for the given error code
PRE  : errorCode
POST : message displayed
*/
void showErrorMessage(int errorCode, char s[])
{
	switch (errorCode)
	{
	case 0:
		printf("\"%s\" - Invalid file name\n\n", s);
		break;
	case -1:
		printf("\"%s\" - too big\n\n", s);
		break;
	case -2:
		printf("\"%s\" - not found\n\n", s);
		break;
	}
}

/**
                Arrays, Strings, Structures, Sorting, Pointers, and

                                Dynamic Allocation of Memory

This program determines the winners at a particular talent competition.

Reading from "performers.txt" . . .
Writing to "performers_out.txt"

The winners of the competition are:
        Ann with a score of 274

Reading from "contestants.txt" . . .
Writing to "contestants_out.txt"

The winners of the competition are:
        Linda with a score of 288
        James with a score of 288
        Marie with a score of 288
        Tina with a score of 288
        Jonathan with a score of 288

"abc.txt" - not found

"test" - Invalid file name

Reading from "test.txt" . . .
Writing to "test_out.txt"

The winners of the competition are:
        John with a score of 258
        David with a score of 258
        Mary with a score of 258
        Andy with a score of 258
        John with a score of 258
        Ann with a score of 258
        Dan with a score of 258


                Thank you for using the program,
                Have a great day!

 */
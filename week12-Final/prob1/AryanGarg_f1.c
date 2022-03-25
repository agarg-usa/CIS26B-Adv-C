/*
 Task 1:

   This program sorts an array of STUDENT structures using the insertion sort algorithm.
   There are two sort functions:
		void insertionSortA(CIS_CLASSES  list[], CIS_CLASSES *pLast); // sort ascending order by class ID
		void insertionSortB(CIS_CLASSES  list[], CIS_CLASSES *pLast); // sort descending order by number of sections
		void insertionSortC(CIS_CLASSES  list[], CIS_CLASSES *pLast); // sort descending order by number of students

REQUIREMENTS:
   1. Replace the three sorting functions with one generic sort:
	  void insertionSort(CIS_CLASSES  list[], CIS_CLASSES *pLast, int compare(void *, void *));
   2. Define a compare function to be used as a parameter for the first call of the generic sort:
			 int compareClassID(void *p1, void *p2);
   3. Define a compare function to be used as a parameter for the second call of the generic sort:
			 int compareNoSections(void *p1, void *p2);
   4. Define a compare function to be used as a parameter for the third call of the generic sort:
		   int compareNoStu(void *p1, void *p2);
   5. Replace the calls for the given three sort functions with calls for the generic sort function
   6. Run the program.
   7. Save the output as a comment at the end of the source file.
   8. Write your name and IDE below

 NAME: Aryan Garg
 IDE: VSCode / GNU GCC
*~*/

#include <stdio.h>
#include <string.h>

#define NUM_CLS 9

typedef struct
{
	char course[10];
	int noSections;
	int sections[16];
	int noStu;
} CIS_CLASSES;

void insertionSort(CIS_CLASSES list[], CIS_CLASSES *pLast, int compare(void *, void *));
void insertionSortA(CIS_CLASSES list[], CIS_CLASSES *pLast);
void insertionSortB(CIS_CLASSES list[], CIS_CLASSES *pLast);
void insertionSortC(CIS_CLASSES list[], CIS_CLASSES *pLast);
void printList(CIS_CLASSES list[], CIS_CLASSES *pLast, char *description);

int compareClassID(void *p1, void *p2);
int compareNoSections(void *p1, void *p2);
int compareNoStu(void *p1, void *p2);

int main(void)
{
	CIS_CLASSES *pLast;
	CIS_CLASSES clsList[NUM_CLS] =
		{
			{"CIS 35A", 2, {61, 63}, 90},
			{"CIS 35B", 1, {62}, 45},
			{"CIS 41A", 3, {1, 2, 61}, 135},
			{"CIS 28", 1, {61}, 50},
			{"CIS 22C", 4, {3, 4, 61, 63}, 220},
			{"CIS 26B", 1, {61}, 35},
			{"CIS 22B", 8, {1, 2, 3, 4, 6, 61, 62, 63}, 380},
			{"CIS 29", 1, {61}, 29},
			{"CIS 22A", 8, {1, 3, 5, 6, 7, 8, 61, 63}, 400},
		};

	pLast = clsList + NUM_CLS - 1;

	printList(clsList, pLast, "Unsorted");

	// first sort
	// insertionSortA(clsList, pLast);
	insertionSort(clsList, pLast, compareClassID);
	printList(clsList, pLast, "Sorted by class ID");

	// second sort
	// insertionSortB(clsList, pLast);
	insertionSort(clsList, pLast, compareNoSections);
	printList(clsList, pLast, "Sorted by number of sections");

	// third sort
	// insertionSortC(clsList, pLast);
	insertionSort(clsList, pLast, compareNoStu);
	printList(clsList, pLast, "Sorted by number of students");

	return 0;
}

int compareClassID(void *p1, void *p2)
{
	CIS_CLASSES *pC1 = (CIS_CLASSES *)p1;
	CIS_CLASSES *pC2 = (CIS_CLASSES *)p2;

	return strcmp(pC1->course, pC2->course);
}

int compareNoSections(void *p1, void *p2)
{
	CIS_CLASSES *pC1 = (CIS_CLASSES *)p1;
	CIS_CLASSES *pC2 = (CIS_CLASSES *)p2;

	return pC2->noSections - pC1->noSections;
}

int compareNoStu(void *p1, void *p2)
{
	CIS_CLASSES *pC1 = (CIS_CLASSES *)p1;
	CIS_CLASSES *pC2 = (CIS_CLASSES *)p2;

	return pC2->noStu - pC1->noStu;
}

void insertionSort(CIS_CLASSES list[], CIS_CLASSES *pLast, int compare(void *, void *))
{
	CIS_CLASSES temp;
	CIS_CLASSES *pCurr;
	CIS_CLASSES *pWalk;

	for (pCurr = list + 1; pCurr <= pLast; pCurr++)
	{
		temp = *pCurr;
		pWalk = pCurr - 1;
		while (pWalk >= list && compare(&temp, pWalk) < 0)
		{
			*(pWalk + 1) = *pWalk;
			pWalk--;
		}
		*(pWalk + 1) = temp;
	}
}

/*~*~*~*~*~*~
	Sort list using Insertion Sort.
	Sort by ascending order of class number
	   Pre   list[] must contain at least one element
			 size is index to last element in list
	   Post  list has been rearranged.
 *~*/
void insertionSortA(CIS_CLASSES list[], CIS_CLASSES *pLast)
{
	CIS_CLASSES temp;
	CIS_CLASSES *pCurr;
	CIS_CLASSES *pWalk;

	for (pCurr = list + 1; pCurr <= pLast; pCurr++)
	{
		temp = *pCurr;
		pWalk = pCurr - 1;
		while (pWalk >= list && strcmp(temp.course, pWalk->course) < 0)
		{
			*(pWalk + 1) = *pWalk;
			pWalk--;
		}
		*(pWalk + 1) = temp;
	}
}

/*~*~*~*~*~*~
	Sort list using Insertion Sort.
	Sort by descending order of number of sections.
	   Pre   list[] must contain at least one element
			 size is index to last element in list
	   Post  list has been rearranged
 *~*/
void insertionSortB(CIS_CLASSES list[], CIS_CLASSES *pLast)
{
	CIS_CLASSES temp;
	CIS_CLASSES *pCurr;
	CIS_CLASSES *pWalk;

	for (pCurr = list + 1; pCurr <= pLast; pCurr++)
	{
		temp = *pCurr;
		pWalk = pCurr - 1;
		while (pWalk >= list && temp.noSections > pWalk->noSections)
		{
			*(pWalk + 1) = *pWalk;
			pWalk--;
		}
		*(pWalk + 1) = temp;
	}
}

/*~*~*~*~*~*~
	Sort list using Insertion Sort.
	Sort by descending order of number of students.
	   Pre   list[] must contain at least one element
			 size is index to last element in list
	   Post  list has been rearranged
 *~*/
void insertionSortC(CIS_CLASSES list[], CIS_CLASSES *pLast)
{
	CIS_CLASSES temp;
	CIS_CLASSES *pCurr;
	CIS_CLASSES *pWalk;

	for (pCurr = list + 1; pCurr <= pLast; pCurr++)
	{
		temp = *pCurr;
		pWalk = pCurr - 1;
		while (pWalk >= list && temp.noStu > pWalk->noStu)
		{
			*(pWalk + 1) = *pWalk;
			pWalk--;
		}
		*(pWalk + 1) = temp;
	}
}

/*~*~*~*~*~*~
	Print list prints.
	   Pre   list[] must contain at least one element
			 size is index to last element in list
	   Post  list has been rearranged
*~*/
void printList(CIS_CLASSES list[], CIS_CLASSES *pLast, char *description)
{
	CIS_CLASSES *pCls;

	printf("%s: \n", description);
	for (pCls = list; pCls <= pLast; pCls++)
	{
		printf("%-10s %2d %3d ", pCls->course, pCls->noSections, pCls->noStu);
		int *pW, *pL;
		for (pW = pCls->sections, pL = pW + pCls->noSections - 1; pW <= pL; pW++)
			printf("%2d ", *pW);
		printf("\n");
	}
	printf("\n");
}

/* Save the output below

Unsorted:
CIS 35A     2  90 61 63
CIS 35B     1  45 62
CIS 41A     3 135  1  2 61
CIS 28      1  50 61
CIS 22C     4 220  3  4 61 63
CIS 26B     1  35 61
CIS 22B     8 380  1  2  3  4  6 61 62 63
CIS 29      1  29 61
CIS 22A     8 400  1  3  5  6  7  8 61 63

Sorted by class ID:
CIS 22A     8 400  1  3  5  6  7  8 61 63
CIS 22B     8 380  1  2  3  4  6 61 62 63
CIS 22C     4 220  3  4 61 63
CIS 26B     1  35 61
CIS 28      1  50 61
CIS 29      1  29 61
CIS 35A     2  90 61 63
CIS 35B     1  45 62
CIS 41A     3 135  1  2 61

Sorted by number of sections:
CIS 22A     8 400  1  3  5  6  7  8 61 63
CIS 22B     8 380  1  2  3  4  6 61 62 63
CIS 22C     4 220  3  4 61 63
CIS 41A     3 135  1  2 61
CIS 35A     2  90 61 63
CIS 26B     1  35 61
CIS 28      1  50 61
CIS 29      1  29 61
CIS 35B     1  45 62

Sorted by number of students:
CIS 22A     8 400  1  3  5  6  7  8 61 63
CIS 22B     8 380  1  2  3  4  6 61 62 63
CIS 22C     4 220  3  4 61 63
CIS 41A     3 135  1  2 61
CIS 35A     2  90 61 63
CIS 28      1  50 61
CIS 35B     1  45 62
CIS 26B     1  35 61
CIS 29      1  29 61

*/

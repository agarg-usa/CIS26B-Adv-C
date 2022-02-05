/*
 CIS 26B: Homework 1A
 ********************
 NAME: Aryan Garg
 IDE(compiler): GCC
*************************************************************************
   Arrays, Strings, Structures, Sorting, Pointers, Functions and Files
   Sort an array of STUDENT structures using the insertion sort algorithm.

   Your task:
        1. Write function named printList() that displays the list to the
           screen and call it in main() as needed to print the sorted and unsorted data.
           Display the sections for each course on the same line, as shown below
                    CIS 41A     3 : 1  2  61
        2. Write a second sort function that sorts the array in descending order
           by the number of sections, then call it in main().
        3. Replace the "Sample Output" below with the updated output.
*/

#include <stdio.h>
#include <string.h>

#define NUM_CLS 9

typedef struct
{
    char  course[10];
    int   noSections;
    int   sections[16];
} CIS_CLASSES;

void insertionSort (CIS_CLASSES  list[], CIS_CLASSES *pLast);
void printList(CIS_CLASSES clsList[], CIS_CLASSES* pLast);
void insertionSortReverse(CIS_CLASSES list[], CIS_CLASSES *pLast);

int main (void)
{
	CIS_CLASSES  clsList[NUM_CLS] =
    {
	    {"CIS 35A", 2, {61, 63}},
        {"CIS 35B", 1, {62}},
        {"CIS 41A", 3, {1, 2, 61}},
        {"CIS 28",  1, {61}},
	    {"CIS 22C", 4, {3, 4, 61, 63}},
        {"CIS 26B", 1, {61}},
        {"CIS 22B", 8, {1, 2, 3, 4, 6, 61, 62, 63}},
        {"CIS 29",  1, {61}},
        {"CIS 22A", 8, {1, 3, 5, 6, 7, 8, 61, 63}},
	};
	CIS_CLASSES *pLast = clsList + NUM_CLS - 1;

    // replace the follwing 8 lines with a call for printList()
	printf("Unsorted data:\n");
	printList(clsList, pLast);


	insertionSort (clsList, pLast);

    // replace the follwing 8 lines with a call for printList()
	printf("Sorted data:\n");
    printList(clsList, pLast);

    // call the second sort here
	insertionSortReverse(clsList, pLast);

    // call the printList() function again
	printf("Sorted data in reverse order:\n");
	printList(clsList, pLast);

	return 0;
}

void printList(CIS_CLASSES clsList[], CIS_CLASSES *pLast)
{
	CIS_CLASSES *pCls;


	for (pCls = clsList; pCls <= pLast; pCls++)
    {
	   printf("%-10s %2d ", pCls->course, pCls->noSections);
       // add more code here to print the sections for this course
       printf("\n");
    }
	printf("\n");
}

/*	========================================================
	Sort list using Insertion Sort.
	   Pre   list[] must contain at least one element
	         size is index to last element in list
	   Post  list has been rearranged.
*/
void insertionSort (CIS_CLASSES  list[], CIS_CLASSES *pLast)
{
	CIS_CLASSES  temp;
	CIS_CLASSES *pCurr;
	CIS_CLASSES *pWalk;

	for (pCurr = list + 1; pCurr <= pLast; pCurr++)
    {
	   temp    = *pCurr;
	   pWalk = pCurr - 1;
       while (pWalk >= list && strcmp(temp.course, pWalk->course) < 0)
       {
             *(pWalk + 1) = *pWalk;
	          pWalk--;
	   }
	   *(pWalk + 1)  = temp;
    }
}

void insertionSortReverse (CIS_CLASSES  list[], CIS_CLASSES *pLast)
{
	CIS_CLASSES  temp;
	CIS_CLASSES *pCurr;
	CIS_CLASSES *pWalk;

	for (pCurr = list + 1; pCurr <= pLast; pCurr++)
    {
	   temp    = *pCurr;
	   pWalk = pCurr - 1;
       while (pWalk >= list && strcmp(temp.course, pWalk->course) > 0)
       {
             *(pWalk + 1) = *pWalk;
	          pWalk--;
	   }
	   *(pWalk + 1)  = temp;
    }
}

/*	================= Sample Output ================= */
/*
 Unsorted data:
 CIS 35A     2
 CIS 35B     1
 CIS 41A     3
 CIS 28      1
 CIS 22C     4
 CIS 26B     1
 CIS 22B     8
 CIS 29      1
 CIS 22A     8

 Sorted data:
 CIS 22A     8
 CIS 22B     8
 CIS 22C     4
 CIS 26B     1
 CIS 28      1
 CIS 29      1
 CIS 35A     2
 CIS 35B     1
 CIS 41A     3

*/
/*    ================= Updated Output ================= */
/*
Unsorted data:
CIS 35A     2
CIS 35B     1
CIS 41A     3
CIS 28      1
CIS 22C     4
CIS 26B     1
CIS 22B     8
CIS 29      1
CIS 22A     8

Sorted data:
CIS 22A     8
CIS 22B     8
CIS 22C     4
CIS 26B     1
CIS 28      1
CIS 29      1
CIS 35A     2
CIS 35B     1
CIS 41A     3

Sorted data in reverse order:
CIS 41A     3
CIS 35B     1
CIS 35A     2
CIS 29      1 
CIS 28      1
CIS 26B     1
CIS 22C     4
CIS 22B     8
CIS 22A     8
 */

/*********************************************************************************
** CIS 26B: Advanced C
******************
** Homework 2B:
**        A Circular Doubly Linked List of Stacks
**********************************************************************************
   This program

   gets an input of temperatures from different cities / states and compiled all the different
   states / cities into a double linked list and all of the temperatures for each of the respective
   cities / states into a stack

   Save the output as a comment at the end of the program.
**********************************************************
**  Written By: Aryan Garg
**  IDE: VScode / Gcc
***************************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"
#include "linked_list.h"

#define FLUSH while (getchar() != '\n')

#ifdef _MSC_VER
#include <crtdbg.h>  // needed to check for memory leaks (Windows only!)
#endif

/**
 * gets user input for file name then reads file into LIST_NODE head
 */
void readFile(LIST_NODE *);
/**
 * displays list first in ascending order then in descending order
 */
void traverseList(LIST_NODE *);
/**
 * repeatedly asks user for a state/city string, then locates and prints most revent temp and average temp
 */
void searchLoop(LIST_NODE *);

int main( void )
{
	LIST_NODE *head = list_init();
	readFile(head);
	traverseList(head);
	searchLoop(head);


    #ifdef _MSC_VER
        printf( _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Memory Leak\n");
    #endif

    return 0;
}

void readFile(LIST_NODE* head)
{
	FILE* fp;
	char inFileName[64];
	printf("Enter input file (0 for default): ");
	scanf("%64s", inFileName);
	if (inFileName[0] == '\0' || inFileName[0] == '0')
	{
		strcpy(inFileName, "temperatures.txt");
	}
	FLUSH;

	fp = fopen(inFileName, "r");
	if(fp == NULL)
	{
		printf("Error opening file.\n");
		return;
	}

	char* name;
	char line[NAME_SIZE];
	int temperature;
	LIST_NODE* currNode;

	// while(fscanf(fp, "%s:%d", name, &temperature) != EOF)
	while(fgets(line, NAME_SIZE, fp) != NULL)
	{
		name = strtok(line, ":");
		temperature = (int) strtol(strtok(NULL, ":"), NULL, 10);
		insert(head, name, &currNode);
		insertIntoStack(currNode, temperature);
	}
}

void traverseList(LIST_NODE* head)
{
	printf("DISPLAYING LIST (ASCENDING)\n");
	LIST_NODE* currNode = head->forw;
	while(currNode != head)
	{
		printf("%s: %d\n", currNode->location, currNode->top->temperature);

		currNode = currNode->forw;
	}

	printf("\nDISPLAYING LIST (DESCENDING)\n");
	currNode = head->back;
	while(currNode != head)
	{
		printf("%s: %d\n", currNode->location, currNode->top->temperature);

		currNode = currNode->back;
	}
}

void searchLoop(LIST_NODE* head)
{
	char locName[NAME_SIZE];
	LIST_NODE* currNode;

	printf("Enter a state/city name (type \"quit\" to quit): ");
	while(fgets(locName, NAME_SIZE, stdin) != NULL)
	{
		strtok(locName, "\n");
		if(strcmp(locName, "quit") == 0)
		{
			break;
		}
		currNode = findNode(head, locName);
		if(currNode != NULL)
		{
			printf("%s: %d°\n", currNode->location, currNode->top->temperature);
			printf("Average Temperature: %.2f°\n", currNode->totalTemp / (float)currNode->count);
		}
		else
		{
			printf("%s not found.\n", locName);
		}

		printf("Enter a state/city name (type \"quit\" to quit): ");
	}
}

/*

Sample Output:

Enter input file (0 for default): 0
DISPLAYING LIST (ASCENDING)
Arizona,Flagstaff: 84
Arizona,Phoenix: 107
Arizona,Tucson: 109
California,Cupertino: 88
California,Los Angeles: 97
California,San Francisco: 82
California,Yreka: 100
Nevada,Reno: 108
Oregon,Portland: 79
Oregon,Salem: 85
Pennsylvania,Philadelphia: 86
Pennsylvania,Pittsburgh: 89

DISPLAYING LIST (DESCENDING)
Pennsylvania,Pittsburgh: 89
Pennsylvania,Philadelphia: 86
Oregon,Salem: 85
Oregon,Portland: 79
Nevada,Reno: 108
California,Yreka: 100
California,San Francisco: 82
California,Los Angeles: 97
California,Cupertino: 88
Arizona,Tucson: 109
Arizona,Phoenix: 107
Arizona,Flagstaff: 84
Enter a state/city name (type "quit" to quit): asdf
asdf not found.
Enter a state/city name (type "quit" to quit): California,Los Angeles
California,Los Angeles: 97°
Average Temperature: 84.50°
Enter a state/city name (type "quit" to quit): qui
qui not found.
Enter a state/city name (type "quit" to quit): quit

*/
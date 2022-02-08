/*
 Task 3: Programming challenge

 This program is based on Examples: 3.15 - 3.19 - book
 Driver program to demonstrate hashing using collision resolution by chaining.

 Write the definition of the linkedListCat function.
 The purpose of the function is to create one big linked list by concatenating
 the linked list in the hash table beginning with the last linked list and
 finishing with the first linked list.

 Example:
 If the user enters the following keys:
 201 102 567 456 654 465 645 quit
 list at index 0 is empty
 list at index 1 is not empty:
 201
 102
 567
 list at index 2 is empty
 list at index 3 is empty
 list at index 4 is not empty:
 456
 654
 465
 645

 The final linked list contains:
 456
 654
 465
 645
 201
 102
 567

 Name: Aryan Garg
 ASSUMPTIONS: the original array of linkedlists passed into the function will be getting modified to NULL
*/

#include <stdio.h>
#include <stdlib.h> // malloc(), free(), exit()
#include <string.h>

#define NUMPOINTERS 5

typedef struct node STUDENTREC;
struct node
{
	char id[10];
	struct node *next;
};

// Function Declarations
int hash(char id[]);
STUDENTREC *insert(char id[],
				   STUDENTREC *student_body[],
				   int hashval);
void traverse(STUDENTREC *student_body[]);
void displayLL(STUDENTREC *list, char *description);

STUDENTREC *linkedListCat(STUDENTREC *student_body[]);

int main(void)
{

	STUDENTREC *student_body[NUMPOINTERS] = {NULL};
	STUDENTREC *person;
	STUDENTREC *oneList;
	char id[10];
	int hashval;

	printf(" ~*~ Hashing using collision resolution by chaining ~*~\n");
	printf("\t Enter Student ID (or quit): ");
	scanf("%s", id);
	while (strcmp(id, "quit"))
	{
		hashval = hash(id);
		person = insert(id, student_body, hashval);
		if (person) // not NULL => duplicate
		{
			printf("Duplicate record!\n");
		}
		printf("\t Enter Student ID (or quit): ");
		scanf("%s", id);
	}
	traverse(student_body);
	oneList = linkedListCat(student_body);
	displayLL(oneList, "Concatenation Result");
	traverse(student_body);
	return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 The purpose of the function is to create one big linked list by concatenating
 the linked list in the hash table beginning with the last linked list and
 finishing with the first linked list.
 */

STUDENTREC *linkedListCat(STUDENTREC *student_body[])
{
	STUDENTREC *one = NULL;
	STUDENTREC *onePtr = NULL;
	STUDENTREC *listPtr = NULL;

	for (int i = NUMPOINTERS - 1; i >= 0; i--)
	{
		if (student_body[i])
		{
			listPtr = student_body[i];
			while (listPtr != NULL)
			{
				if(one == NULL)
				{
					one = listPtr;
					onePtr = one;
				}
				else
				{
					onePtr->next = listPtr;
					onePtr = listPtr;
				}

				listPtr = listPtr->next;
			}

			student_body[i] = NULL;
		}
	}

	return one;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Hash Student ID by summing the cubes
	of the ASCII value of characters and then take
	the modulo of this sum.
*/
int hash(char id[])
{
	long sum = 0;

	while (*id) // != '\0'
	{
		sum += *id * *id * *id;
		id++;
	}
	return sum % NUMPOINTERS;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Insert a new Student ID into the
	array of student records, at index equal to
	hashvalue
*/
STUDENTREC *insert(char id[],
				   STUDENTREC *student_body[],
				   int hashval)
{
	STUDENTREC **mover; // Use ** to write elegant code

	mover = &student_body[hashval]; // mover points to address of studentbody[hashval] linked list
	while (*mover)
	{
		if (strcmp(id, (*mover)->id) == 0)
			return *mover;		   // if we find the same id in a hashvalue return the pointer
		mover = &((*mover)->next); // move mover to the next pointer
	}
	if ((*mover = (STUDENTREC *)malloc(sizeof(STUDENTREC))) == NULL) // insert a new node
	{
		printf("Malloc error in insert!\n");
		exit(1);
	}
	strcpy((*mover)->id, id);
	(*mover)->next = NULL; // set the link of the new node to NULL
	printf("%s has been placed in the list at location %d.\n", (*mover)->id, hashval);

	return NULL;
}
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Traversing the lists in a hash table
*/
void traverse(STUDENTREC *student_body[])
{
	int i;

	for (i = 0; i < NUMPOINTERS; i++)
	{
		printf("Contents of list %2d\n", i);
		printf("--------------------\n");

		displayLL(student_body[i], NULL);
		printf("\n");
	}
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Traversing a linked list
*/
void displayLL(STUDENTREC *list, char *description)
{
	if (list) // != NULL
	{
		if (description) // != NULL
		{
			printf("%s\n", description);
			printf("--------------------\n");
		}
		STUDENTREC **mover; // Use ** for fun and practice
							// not needed for traverse
		for (mover = &list; *mover; mover = &(*mover)->next)
		{ // &((*mover)->next)
			printf("%s\n", (*mover)->id);
		}
	}
	else
		printf("Empty!");

	printf("\n");
}
/*
 ~*~ Hashing using collision resolution by chaining ~*~
	 Enter Student ID (or quit): 201
201 has been placed in the list at location 1.
	 Enter Student ID (or quit): 102
102 has been placed in the list at location 1.
	 Enter Student ID (or quit): 567
567 has been placed in the list at location 1.
	 Enter Student ID (or quit): 456
456 has been placed in the list at location 4.
	 Enter Student ID (or quit): 654
654 has been placed in the list at location 4.
	 Enter Student ID (or quit): 465
465 has been placed in the list at location 4.
	 Enter Student ID (or quit): 645
645 has been placed in the list at location 4.
	 Enter Student ID (or quit): quit
Contents of list  0
--------------------
Empty!

Contents of list  1
--------------------
201
102
567


Contents of list  2
--------------------
Empty!

Contents of list  3
--------------------
Empty!

Contents of list  4
--------------------
456
654
465
645


Concatenation Result
--------------------
456
654
465
645
201
102
567

Contents of list  0
--------------------
Empty!

Contents of list  1
--------------------
Empty!

Contents of list  2
--------------------
Empty!

Contents of list  3
--------------------
Empty!

Contents of list  4
--------------------
Empty!
 */

/*
Sample Output:
 ~*~ Hashing using collision resolution by chaining ~*~
         Enter Student ID (or quit):   201 102 567 456 654 465 645 quit
201 has been placed in the list at location 1.
         Enter Student ID (or quit): 102 has been placed in the list at location 1.
         Enter Student ID (or quit): 567 has been placed in the list at location 1.
         Enter Student ID (or quit): 456 has been placed in the list at location 4.
         Enter Student ID (or quit): 654 has been placed in the list at location 4.
         Enter Student ID (or quit): 465 has been placed in the list at location 4.
         Enter Student ID (or quit): 645 has been placed in the list at location 4.
         Enter Student ID (or quit): Contents of list  0
--------------------
Empty!

Contents of list  1
--------------------
201
102
567


Contents of list  2
--------------------
Empty!

Contents of list  3
--------------------
Empty!

Contents of list  4
--------------------
456
654
465
645


Concatenation Result
--------------------
456
654
465
645
201
102
567

Contents of list  0
--------------------
Empty!

Contents of list  1
--------------------
Empty!

Contents of list  2
--------------------
Empty!

Contents of list  3
--------------------
Empty!

Contents of list  4
--------------------
Empty!
*/
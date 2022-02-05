/*

A linear list is a list in which all elements have a unique successor
arrays, linked list

*/

typedef struct node
{
	int data;
	struct node *next;
} NODE;

/*
Memory:
program

global variables

local variables, parameters, static allocation of mem (stack)

dynamic allocation of mem (heap)
*/

typedef struct
{
	int count;
	NODE *head;
} LIST;

/*
above is like a "header" struct for a linked list

*/
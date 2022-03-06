#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#define NAME_SIZE 200
#define DUMMY_TRAILER '\177'

#include "stack.h"

typedef struct list_node{
	char location[NAME_SIZE];
	struct list_node *forw;
	struct list_node *back;
	STACK_NODE *top;
	int count; // count in stack
	int totalTemp;
} LIST_NODE;
/**
 * creates a senitenal node for the head of the link list
 */
LIST_NODE *list_init(void);
/**
 * Inserts a node into the list
 * returns 1 if it added, 0 if it found the node already in the list
 */
int insert(LIST_NODE *list, char* name, LIST_NODE** ref);
/**
 * Given a node, inserts a temperature into its stack
 */
void insertIntoStack(LIST_NODE* node, int temperature);
/**
 * finds a node with the given name
 */
LIST_NODE* findNode(LIST_NODE* list, char* loc);

#endif
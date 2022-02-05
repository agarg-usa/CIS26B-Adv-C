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

LIST_NODE *init_list(void);
int insert(LIST_NODE *list, char* name, LIST_NODE** ref);
void insertIntoStack(LIST_NODE* node, int temperature);
LIST_NODE* findNode(LIST_NODE* list, char* loc);

#endif
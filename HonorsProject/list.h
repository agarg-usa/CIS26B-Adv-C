#ifndef LIST_H
#define LIST_H

#define ASCII_START 1 // inclusive
#define ASCII_END 127 // exclusive
// ascii range minus NULL and DEL char

#include "tree.h"

typedef struct list_node{
	struct list_node* next;
	struct list_node* prev;
	TREE_NODE* tree;
	int totalWeight;
} LIST_NODE;

LIST_NODE *list_init(void);
LIST_NODE *list_search(LIST_NODE *head, char data);
void list_float_up(LIST_NODE* node);
LIST_NODE* list_insert(LIST_NODE *head, char data);

void list_dump(LIST_NODE *head);
void list_assemble(LIST_NODE* node); // assembles with the node to its left 




#endif
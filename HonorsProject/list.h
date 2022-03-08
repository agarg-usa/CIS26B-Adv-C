#ifndef LIST_H
#define LIST_H

#define ASCII_START 1 // inclusive
#define ASCII_END 127 // exclusive
// ascii range minus NULL and DEL char
// you can adjust this to include the extended ascii characters

#include "tree.h"

/*
The list is a doubly linked list of nodes with the first element being a sentinel node.
Each node contains a tree node
*/
typedef struct list_node{
	struct list_node* next;
	struct list_node* prev;
	TREE_NODE* tree;
	int totalWeight;
} LIST_NODE;

/*
Allocates a list with characters from ASCII_START to ASCII_END
*/
LIST_NODE *list_init(void);

/*
Searches a list for a node with the corresponding character data
(only works before the trees have been assembled)
*/
LIST_NODE *list_search(LIST_NODE *head, char data);

/*
To keep the list sorted, this function floats up a node until the list is sorted
*/
void list_float_up(LIST_NODE* node);

/*
Increases the weight of the node with the corresponding character data
*/
LIST_NODE* list_insert(LIST_NODE *head, char data);

/*
For debugging purposes, dumps the list
*/
void list_dump(LIST_NODE *head);

/*
Given a node, the list will take this node and the previous node and put them together.
With repeated calls this can be used to create a huffman tree
*/
void list_assemble(LIST_NODE* node); // assembles with the node to its left




#endif
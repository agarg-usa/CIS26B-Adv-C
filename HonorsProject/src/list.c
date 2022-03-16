#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"
#include "tree.h"

LIST_NODE* list_init(void)
{
	LIST_NODE* head = (LIST_NODE*)malloc(sizeof(LIST_NODE));
	head->totalWeight = __INT_MAX__;
	head->tree = NULL;

	LIST_NODE *curr, *prev = head;
	TREE_NODE *currTree;
	for(unsigned char i = ASCII_START; i < ASCII_END; i++)
	{
		curr = (LIST_NODE*)malloc(sizeof(LIST_NODE));
		prev->next = curr;
		curr->prev = prev;
		curr->totalWeight = 0;
		currTree = tree_init(i);
		curr->tree = currTree;

		prev = curr;
	}

	curr->next = head;
	head->prev = curr;
	// make this a doubly linked list
	return head;
}

LIST_NODE *list_search(LIST_NODE *head, char data)
{
	LIST_NODE *curr = head->next;
	while(curr != NULL)
	{
		if(curr->tree->data == data)
		{
			return curr;
		}
		curr = curr->next;
	}

	return NULL;
}

void list_float_up(LIST_NODE* node)
{
	LIST_NODE *prev,  *curr = node;
	while(curr->prev->totalWeight < curr->totalWeight) // we need to float this node up
	{
		prev = curr->prev;

		curr->prev = prev->prev;
		prev->next = curr->next;

		curr->next = prev;
		prev->prev = curr;

		curr->prev->next = curr;
		prev->next->prev = prev;

	}
}


LIST_NODE* list_insert(LIST_NODE *head, char data)
{
	LIST_NODE *curr = list_search(head, data);
	if(curr == NULL)
	{
		return NULL;
	}

	curr->totalWeight++;
	curr->tree->weight++;
	list_float_up(curr);
	return curr;
}

void list_dump(LIST_NODE *head)
{
	LIST_NODE *curr = head->next;
	while(curr != head)
	{
		printf("%c (%d): %d\n", curr->tree->data, curr->tree->data, curr->totalWeight);
		curr = curr->next;
	}
}

void list_assemble(LIST_NODE* node)
{
	LIST_NODE *curr = node;
	LIST_NODE *prev = curr->prev;  // prev is the node to the left

	TREE_NODE *newTree = tree_init(EMPTY_TREE_NODE);
	newTree->left = prev->tree;
	newTree->right = curr->tree;
	newTree->weight = prev->totalWeight + curr->totalWeight;

	curr->tree = newTree;
	curr->totalWeight = newTree->weight;

	prev->prev->next = curr;
	curr->prev = prev->prev; // cut out prev from the list
	free(prev); // free the old node

	list_float_up(curr);
}
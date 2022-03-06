#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *next;
} NODE;

int add(NODE* currNode);

int main(void)
{
	NODE node1, node2, node3, node4;
	node1.data = 1;
	node2.data = 2;
	node3.data = 20;
	node4.data = 30;

	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = NULL;

	add(&node1);
	printf("%d\n", node1.data);
	printf("%d\n", node2.data);
	printf("%d\n", node3.data);
	printf("%d\n", node4.data);
}

int add(NODE* currNode)
{
	if(currNode->next == NULL)
	{
		return currNode->data;
	}

	currNode->data += add(currNode->next);
	return currNode->data;
}
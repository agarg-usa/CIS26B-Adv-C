#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linked_list.h"
#include "stack.h"

LIST_NODE* createNewNode()
{
	LIST_NODE *list;
	list = (LIST_NODE *) malloc(sizeof (LIST_NODE));
    if (!list)
    {
        printf("Error in creating linked list node!\n");
        exit(1);
    }
	list->count = 0;
	list->totalTemp = 0;
	return list;
}

LIST_NODE *list_init(void)
{
    LIST_NODE *list = createNewNode();

    list->location[0] = DUMMY_TRAILER;
    list->location[1] = '\0';
    list->forw = list;
    list->back = list;

    return list;
}

int insert(LIST_NODE *list, char *data, LIST_NODE** ref)
{
	LIST_NODE *curr = list->forw;
    LIST_NODE *prev = list;
    LIST_NODE *pnew;

    // search
    while (strcmp(data,curr->location) > 0)
	// if we ever get to the sent node, strcmp will be neg
    {
        prev = curr;
        curr = curr->forw;
    }

    if (strcmp(data, curr->location) )
	// not a duplicate
    {
        pnew = createNewNode();
        strcpy(pnew->location, data);
        pnew->forw = curr;
        pnew->back = prev;
        prev->forw = pnew;
        curr->back = pnew;

		*ref = pnew;
		return 0;
    }
	else
	{
		*ref = curr;
		return 1;
	}
}

void insertIntoStack(LIST_NODE* node, int temperature)
{
	node->top = push(node->top, temperature);
	node->count++;
	node->totalTemp += temperature;
}

LIST_NODE* findNode(LIST_NODE* list, char* loc)
{
	LIST_NODE *curr = list->forw;
	while (curr != list && strcmp(loc, curr->location) != 0)
	{
		curr = curr->forw;
	}

	if(curr == list)
	{
		return NULL;
	}
	return curr;
}

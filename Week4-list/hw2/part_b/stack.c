#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stack.h"

STACK_NODE* push(STACK_NODE *top, int temperature)
{
	STACK_NODE *newNode = (STACK_NODE*)malloc(sizeof(STACK_NODE));
	newNode->temperature = temperature;
	newNode->next = top;
	return newNode;
}

STACK_NODE *pop(STACK_NODE **stack)
{
    STACK_NODE *first;

    if (*stack == NULL) return NULL;
    first = *stack;
    *stack = (*stack)->next;
    first->next = NULL;

    return first;
}
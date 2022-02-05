#ifndef STACK_H
#define STACK_H

typedef struct stack_node{
	int temperature;
	struct stack_node *next;
} STACK_NODE;
/**
 * pushes a new stack node onto the stack and returns a pointer to the top of the stack
 */
STACK_NODE* push(STACK_NODE *top, int temperature);

/**
 * pops the top node off the stack and returns a pointer to the top of the stack
 * changes stack pointer to the new top node
 */
STACK_NODE* pop(STACK_NODE **stack);


#endif
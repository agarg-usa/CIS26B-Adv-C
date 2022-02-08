/*
 Task 2: Debugging

  There are a number of errors in the following program.
  All errors are located in main() and structure definitions.
  Function declarations and definitions are correct!
  Locate all errors, fix them (as shown below), run the program and save its output
  as a comment at the end of the source file.

  Example:
     int num = 10;
     int *ptr;
     num = &ptr; // <== Error: Comment the line and write the correct line below
                 // Write a short justification where appropriate
     // num = &ptr; // Error #1
     ptr = &num;
 Name:
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define DUMMY_TRAILER '\177'
// octal ASCII code of the
// last character in the ASCII table

#define NUM_STU 9

typedef struct
{
    char  id[5]; //error#1 this should be a length of 5 for the \0 character
    int   quizzes[10];
} CIS_STU;

// Stack and Queue Node
typedef struct node NODE;
struct node
{
    CIS_STU   data;
    // node *next; // ERROR #2, node is not a valid data type, struct node is though
	struct node *next;
};

// Doubly Linked List Node
typedef struct d_node D_NODE;
struct d_node
{
    CIS_STU data;
    // NODE *forw; //ERROR #3, the next node should be of type D_NODE not NODE
    // NODE *back;
	struct d_node *forw;
	struct d_node *back;
};

// Stack Functions
NODE *push(NODE *stack, const CIS_STU *pStu);
NODE *pop(NODE **stack);

// Queue Functions
void enqueue(NODE **queue, NODE **rear, const CIS_STU *pStu);
NODE *dequeue(NODE **queue, NODE **rear);

// Doubly Linked List Functions
D_NODE *init_list(void);
int   insert(D_NODE *list, const CIS_STU *pStu);
void  traverse_forw(D_NODE *list);
void  traverse_back(D_NODE *list);

// Other Functions
void printClass(const CIS_STU *pStu);

int main (void)
{
    CIS_STU  clsList[NUM_STU] =
    {
        {"1230", {10, 9, 10, 8, 9, 9, 10, 5, 9, 8}},
        {"1231", {9, 10, 8, 9, 9, 10, 5, 9, 8, 7}},
        {"1232", {7, 8, 9, 9, 10, 5, 9, 8, 10, 9}},
        {"1233", {6, 9, 9, 10, 5, 8, 9, 8, 10, 10,}},
        {"1234", {9, 10, 5, 9, 10, 9, 10, 8, 9, 8}},
        {"1235", {10, 5, 9, 10, 8, 9, 9, 10, 9, 8}},
        {"1236", {8, 10, 5, 9, 10, 9, 10, 8, 9, 8}},
        {"1237", {5, 10, 9, 10, 8, 9, 9, 10, 9, 8}},
        {"1238", {10, 9, 10, 8, 9, 9, 10, 5, 9, 8}},
    };

    NODE *stack = NULL;
    NODE *top = NULL;
    NODE *queue = NULL, *rear = NULL;
    NODE *front;
    D_NODE *list;

    list = init_list();
    // build stack and queue with data from an array of CIS_STU structures
    srand((unsigned int)time(NULL));

    int count = rand() % 9;

    for ( int n = 0; n < count; n++)
    {
        // int i = rand() % NUM_STU + 1; // Error #4 this will make the index go out of bounds
		int i = rand() % NUM_STU;

        int duplicate = insert(list, &(clsList[i]) );
        if(duplicate)
        {
            // already in the list!
            //push(stack, clsList[i]); error #5, you need to reassign stack to the return value of push and clsList needs to be a pointer
			stack = push(stack, &(clsList[i]));
            //  enqueue(&queue, &rear, clsList[i]); ERROR #6 - clsList needs to be a pointer
			enqueue(&queue, &rear, &(clsList[i]));

         }
    }
    // display list
    printf("\nLIST contents (forwards):\n");
    traverse_forw(list);
    printf("\nLIST contents (backwards):\n");
    traverse_back(list);

    // display stack
    // if (top) error #7, top is just for traversing. Stack is a pointer to a node
	if(stack)
    {
        printf("\nSTACK contents from top to bottom:\n");
        // while ((top = pop(stack))) error #8, pop takes in a pointer to a pointer, stack is just a pointer
		while((top = pop(&stack)))
        {
            // printClass(top->data); error#9 we need to pass in the pointer of data
			printClass(&top->data);
            // free(stack); error #10 this should be free(top)
			free(top);
        }
    }
    else
        printf ("Empty Stack!\n");


    // display queue
    // if (front) Error#11 same error as above, front is just for traversing, Queue is the actual node
	if(queue)
    {
        printf("\nQUEUE contents from front to rear:\n");
        // while ((front = dequeue( queue,  rear))) error #12, dequeue takes in a pointer to a pointer
		while ((front = dequeue(&queue, &rear)))
        {
            // printClass(front->data); Error #13: we need to pass in the pointer of data
			printClass(&front->data);
            // free(queue); error #14 this should be free(front)
			free(front);
        }
    }
    else
        printf ("Empty Queue!\n");

    return 0;
}
/***************************************************
 Displays the fileds of a CIS_CLASS structure
 Pre   pCls - a pointer to a CIS_CLASS structure
 Post
 */
void printClass(const CIS_STU *pCls)
{
    printf("%-10s %2d\n", pCls->id, pCls->quizzes[0]);
}

// Stack Functions

/***************************************************
 Stack Insert: insert in the beginning
 */
NODE *push(NODE *stack, const CIS_STU *pCls)
{
    NODE *pnew;

    pnew = (NODE *) malloc(sizeof (NODE));
    if (!pnew)
    {
        printf("... error in push!\n");
        exit(1);
    }
    pnew->data = *pCls;
    pnew->next = stack;
    stack = pnew;

    return stack;
}

/***************************************************
 Stack Delete: delete the first node
 */
NODE *pop(NODE **stack)
{
    NODE *first;

    if (*stack == NULL) return NULL;
    first = *stack;
    *stack = (*stack)->next;
    first->next = NULL;

    return first;
}

// Queue Functions

/***************************************************
 Queue Insert: insert at the end
 */
void enqueue(NODE **queue, NODE **rear, const CIS_STU *pCls)
{
    NODE *pnew;

    pnew = (NODE *) malloc(sizeof (NODE));
    if (!pnew)
    {
        printf("... error in enqueue!\n");
        exit(1);
    }
    pnew->data = *pCls;
    pnew->next = NULL;
    if (*queue == NULL) *queue = pnew;
    else (*rear)->next = pnew;
    *rear = pnew;
    return;
}

/***************************************************
 Queue Delete: remove the first node
 */
NODE *dequeue(NODE **queue, NODE **rear)
{
    NODE *first;

    if (*queue == NULL) return NULL;
    first = *queue;
    *queue = (*queue)->next;
    if (*queue == NULL) *rear = NULL;
    first->next = NULL;

    return first;
}

// Doubly Linked List Functions
/***************************************************
    Initialization of a circularly doubly-linked
    list with one sentinel node
*/
D_NODE *init_list(void)
{
    D_NODE *list;

    // allocate the sentinel node
    list = (D_NODE *) malloc(sizeof (D_NODE));
    if (!list)
    {
        printf("Error in init_list!\n");
        exit(1);
    }
    list->data.id[0] = DUMMY_TRAILER;
    list->data.id[1] = '\0';
    list->forw = list;
    list->back = list;

    return list;
}

/***************************************************
    Insert a node in a sorted circularly
    doubly-linked list with one sentinel node
        return 1 - if duplicate
        return 0 - otherwise
*/
int insert(D_NODE *list, const CIS_STU *data)
{
    D_NODE *curr = list->forw;
    D_NODE *prev = list;
    D_NODE *pnew;
    int   duplicate = 1;

    // search
    while (strcmp(data->id, curr->data.id) > 0)
    {
        prev = curr;
        curr = curr->forw;
    }

    if (strcmp(data->id, curr->data.id) )
    {
        duplicate = 0; // not a duplicate
        pnew = (D_NODE *) malloc(sizeof (D_NODE));
        if (!pnew)
        {
            printf("Fatal memory allocation error in insert!\n");
            exit(3);
        }
        pnew->data = *data;
        pnew->forw = curr;
        pnew->back = prev;
        prev->forw = pnew;
        curr->back = pnew;
    }
    return duplicate;
}

/***************************************************
    Traverses forward a circularly doubly-linked
    list with one sentinel node to print out the
    contents of each node
*/
void traverse_forw(D_NODE *list)
{
    list = list->forw; // skip the dummy node
    while (list->data.id[0] != DUMMY_TRAILER)
    {
        printClass(&list->data);
        list = list->forw;
    }
}

/***************************************************
    Traverses backward a circularly doubly-linked
    list with one sentinel node to print out the
    contents of each node
*/
void traverse_back(D_NODE *list)
{
    list = list->back; // skip the dummy node
    while (list->data.id[0] != DUMMY_TRAILER)
    {
        printClass(&list->data);
        list = list->back;
    }
}



/*    ================= Sample Output ================= */
/*
 LIST contents (forwards):
 1232        7
 1235       10
 1237        5

 LIST contents (backwards):
 1237        5
 1235       10
 1232        7
 Empty Stack!
 Empty Queue!
 */

/*    ================= Sample Output ================= */
/*

 LIST contents (forwards):
 1230       10
 1232        7
 1233        6

 LIST contents (backwards):
 1233        6
 1232        7
 1230       10

 STACK contents from top to bottom:
 1233        6
 1232        7
 1230       10
 1230       10
 1232        7

 QUEUE contents from front to rear:
 1232        7
 1230       10
 1230       10
 1232        7
 1233        6
 */



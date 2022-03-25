/*
   Task 3:

	This assignment is based on your last homework assignment.
	A function named buildLine() is called as shown in main().
	The purpose of buildLine() is to create a string with all
	"identifiers" with the same line number from the BST.

 Example
 Assume the input file contains the following text:

 row, row,
 row your boat
 Row, row your boat.

 ~*~ Cross-Reference List ~*~
	 1|
	 2| row, row,
	 3| row your boat
	 4| Row, row your boat.
	 5|
 Cross-reference list made at: Mon Mar 15 17:19:30 2021
 Row  4
 boat 3 4
 row  2 3 4
 your 3 4

 The following call for buildLine():
	 line = buildLine(root, 3, maxLineNo);
 returns the string: "boat, row, your."
 Notice that the identifiers are separated by comma and space
 and that the string ends with a dot.

 If called as shown below
	 line = buildLine(root, 5, maxLineNo);
 returns an empty string: ""

 If the line number is invalid it returns NULL.

   REQUIREMENTS:

	1. Write a prototype declaration of the buildLine() function
	2. Write the definition of the buildLine() function:
		  - it validates lineNo
		  - it calls _buildLine(), a recursive function to create the string
			  - write a prototype declaration of the _buildLine() function
			  - write the definition of the recursive _buildLine() function
	3. Clean compile: compile with no errors
	   (no need to run it: it is incomplete, and you do not have to finish it!)

	4. Write your name and IDE below

	NAME: Aryan Garg
	IDE: VSCode / Gcc
   *~*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_CHARS 500

typedef struct q_node
{
	int num;
	struct q_node *next;
} Q_NODE;

typedef struct t_node
{
	struct t_node *left;
	char *identifier; // a dynamically allocated string
	Q_NODE *front;
	Q_NODE *rear;
	struct t_node *right;
} T_NODE;

char* buildLine(T_NODE *root, int lineNo, int maxLineNo);
void _buildLine(T_NODE *root, int lineNo, char **line);

int main(void)
{

	T_NODE *root = NULL;
	int maxLineNo = 5; // the number of lines in the input file
	int lineNo = 3;
	char *line; // a dynamically allocated string
	// Lots of code here…to build a BST
	// Each tree node has a queue of integers
	line = buildLine(root, lineNo, maxLineNo);
	puts(line);
	return 0;
}

char* buildLine(T_NODE* root, int lineNo, int maxLineNo)
{
	if(lineNo < 1 || lineNo > maxLineNo)
	{
		return "";
	}

	char *line = (char*)malloc(sizeof(char) * MAX_LINE_CHARS);
	line[0] = 0;
	_buildLine(root, lineNo, &line);

	if(strlen(line) != 0)
	{
		line[strlen(line) - 1] = 0;
		line[strlen(line) - 2] = '.';
	}

	return line;
}

void _buildLine(T_NODE* root, int lineNo, char **line)
{
	if(root == NULL)
	{
		return;
	}

	_buildLine(root->left, lineNo, line);

	Q_NODE* iter = root->front;
	while(iter != NULL)
	{
		if(iter->num == lineNo)
		{
			if(strlen(*line) + strlen(root->identifier) + 3 > MAX_LINE_CHARS)
			{
				return;
			}
			
			strcat(*line, root->identifier);
			strcat(*line, ", ");
			break;
		}
		iter = iter->next;
	}

	_buildLine(root->right, lineNo, line);
}

/*~*~*~*~*~*~

*~*/

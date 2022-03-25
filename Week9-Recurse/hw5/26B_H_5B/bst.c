#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bst.h"

void insert(NODE** root, char* word, int index)
{
	if(*root == NULL)
	{
		NODE* newNode = (NODE*)malloc(sizeof(NODE));
		newNode->left = NULL;
		newNode->right = NULL;
		strcpy(newNode->word, word);
		newNode->occurrences[index] = 1;
		*root = newNode;
		return;
	}

	if(strcmp((*root)->word, word) == 0)
	{
		(*root)->occurrences[index]++;
	}
	else if(strcmp((*root)->word, word) > 0)
	{
		insert(&(*root)->left, word, index);
	}
	else
	{
		insert(&(*root)->right, word, index);
	}
}

void writeTreeReferences(NODE* root, FILE* out)
{
	if(root == NULL)
	{
		return;
	}

	writeTreeReferences(root->left, out);
	fprintf(out, "%s: ", root->word);
	for(int i = 0; i < MAX_OCCURRENCES; i++)
	{
		if(root->occurrences[i] > 0)
		{
			fprintf(out, "%d ", i);
		}
	}
	fprintf(out, "\n");
	writeTreeReferences(root->right, out);
}
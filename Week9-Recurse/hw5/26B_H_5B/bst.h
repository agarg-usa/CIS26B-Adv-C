#ifndef TREE_H
#define TREE_H

#define MAX_OCCURRENCES 100
#define MAX_WORD_SIZE 100

typedef struct node{
	struct node* left;
	struct node* right;
	char word[MAX_WORD_SIZE];
	int occurrences[MAX_OCCURRENCES];
} NODE;

void insert(NODE** root, char* word, int index);
void writeTreeReferences(NODE* root, FILE* fp);

#endif
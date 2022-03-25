#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "bst.h"

#define LINE_BUFFER_SIZE 4096

NODE* buildTree(FILE* in);
void buildOutput(FILE* in, FILE* out, NODE* root);

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Usage: <input file> <output file>\n");
		return 1;
	}

	char *input_file = argv[1];
	char *output_file = argv[2];

	// char* input_file = "song.c";
	// char* output_file = "out.txt";

	FILE *input = fopen(input_file, "r");
	FILE *output = fopen(output_file, "w");

	if(input == NULL)
	{
		printf("Error: could not open input file\n");
		return 1;
	}

	if(output == NULL)
	{
		printf("Error: could not open output file\n");
		return 1;
	}

	NODE* root = buildTree(input);
	rewind(input);
	buildOutput(input, output, root);

	fclose(input);
	fclose(output);
}

NODE* buildTree(FILE* in)
{
	NODE* head = NULL;

	char line[LINE_BUFFER_SIZE];
	char* word;
	int lineNum = 0;
	while(fgets(line, LINE_BUFFER_SIZE, in))
	{
		strtok(line, "\r\n"); // get rid of trailing newline chars
		lineNum++;
		word = strtok(line, " ");
		while(word != NULL)
		{
			insert(&head, word, lineNum);
			word = strtok(NULL, " ");
		}
	}

	return head;
}

char* getTimeStamp()
{
	time_t t = time(NULL);
	return ctime(&t);
}

void buildOutput(FILE* in, FILE* out, NODE* root)
{
	fprintf(out, "~*~ Cross-Reference List ~*~\n\n");

	int lineNum = 0;
	char line[LINE_BUFFER_SIZE];

	while(fgets(line, LINE_BUFFER_SIZE, in))
	{
		lineNum++;
		fprintf(out, "%d | %s", lineNum, line);
	}

	fprintf(out, "\n\nCross-reference list made at: %s", getTimeStamp());

	writeTreeReferences(root, out);
}
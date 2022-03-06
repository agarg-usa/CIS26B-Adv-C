#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"
#include "tree.h"
#define DEFAULT_INPUT_FILE "in.txt"
#define DEFAULT_OUTPUT_FILE "out.txt"
#define MAX_INPUT_SIZE 100
#define FLUSH while (getchar() != '\n')

LIST_NODE *readFile();
void buildTree(LIST_NODE *head);
int getOption();
void printBin(char data);

int main(void)
{
	LIST_NODE *head = readFile();
	buildTree(head);
	TREE_NODE *root = head->next->tree;
	// tree_print(root, 0, TREE_PRINT_OPTION_WEIGHTS_ONLY);

	MAP_NODE *map = map_init(root);
	// map_print(map);

	char menu[] = "MENU OPTIONS:\n"
				  "\t1. Print Character Weights\n"
				  "\t2. Print Tree\n"
				  "\t3. Print Huffman Code for All Character\n"
				  "\t4. Print Huffman Code for a Character\n"
				  "\t5. Print Huffman Code for a Word\n"
				  "\t6. Decode An Encoded Word\n"
				  "\t7. Encode File\n"
				  "\t8. Decode File\n"
				  "\t9. Exit\n";

	while (1)
	{
		printf("%s", menu);
		char option;
		scanf("%c", &option);
		FLUSH;

		switch (option)
		{
		case '1':
			print_char_weights(map);
			break;
		case '2':
		{
			int option = getOption();
			if (option != -1)
			{
				tree_print(root, 0, option);
			}
			break;
		}
		case '3':
		{
			int option = getOption();
			if (option != -1)
			{
				map_print(map, option);
			}
			break;
		}
		case '4':
		{
			printf("Enter a character: ");
			char c;
			scanf("%c", &c);
			FLUSH;
			printf("%s\n", get_map_node(map, c)->bin);
			break;
		}
		case '5':
		{
			printf("Enter a word: ");
			char word[MAX_INPUT_SIZE];
			scanf("%100s", word);
			FLUSH;

			printf("ASCII REPERSENETATION: ");
			for (int i = 0; i < strlen(word); i++)
			{
				printBin(word[i]);
			}
			printf("\n");
			printf("HUFFMAN CODE: ");
			for (int i = 0; i < strlen(word); i++)
			{
				printf("%s", get_map_node(map, word[i])->bin);
			}
			printf("\n");
			break;
		}
		case '6':
			break;
		case '7':
			break;
		case '8':
			break;
		case '9':
			return 0;
		default:
			printf("Invalid option\n");
		}
	}
}

LIST_NODE *readFile()
{
	char filename[MAX_INPUT_SIZE];

	printf("Enter input file name ( 0 for default: %s ): ", DEFAULT_INPUT_FILE);
	scanf("%100s", filename);
	FLUSH;

	if (strcmp(filename, "0") == 0)
	{
		strcpy(filename, DEFAULT_INPUT_FILE);
	}

	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}

	LIST_NODE *head = list_init();

	char c;
	while (fscanf(fp, "%c", &c) != EOF)
	{
		if (c == ASCII_START - 1 || c == ASCII_END)
		{
			continue; // skip NULL and DEL
		}
		list_insert(head, c);
	}
	// list_dump(head);

	fclose(fp);
	return head;
}

void buildTree(LIST_NODE *head)
{
	LIST_NODE *lastElem = head->prev; // start from the last element
	while (lastElem->prev != head)
	{
		list_assemble(lastElem);
		lastElem = head->prev;
	}
}

int getOption()
{
	int option;
	char menu[] = "Select an option:\n"
				  "\t1. Print All Characters\n"
				  "\t2. Print All Alpha Characters\n"
				  "\t3. Print All Characters with Weights\n";
	printf("%s", menu);
	scanf("%d", &option);
	FLUSH;
	if (option < 1 || option > 3)
	{
		printf("Invalid option\n");
		return -1;
	}
	else if (option == 1)
	{
		return PRINT_OPTION_NONE;
	}
	else if (option == 2)
	{
		return PRINT_OPTION_CHARS_ONLY;
	}
	else if (option == 3)
	{
		return PRINT_OPTION_WEIGHTS_ONLY;
	}

	return -1;
}

void printBin(char data)
{
	for (int i = 7; i >= 0; i--)
	{
		printf("%d", (data >> i) & 1);
	}
}
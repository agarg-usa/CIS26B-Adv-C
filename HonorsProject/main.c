#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"
#include "tree.h"
#define DEFAULT_INPUT_FILE "in.txt"
#define DEFAULT_OUTPUT_FILE "out.txt"
#define MAX_INPUT_SIZE 100
#define FLUSH while (getchar() != '\n')

/*
Gets the file name from the user and reads the file into a LIST structure.
Returns the head of the LIST structure.
*/
LIST_NODE *readFile();

/*
Takes in the LIST_NODE head and will build the tree from the LIST structure using
the list_assemble() function
*/
void buildTree(LIST_NODE *head);

/*
Helper method that gets the user input for the different options on printing out the tree
*/
int getOption();

/*
prints out the binary numbers in a char
*/
void printBin(char data);

/*
Gets the user input for a word and prints the huffman code repersenting that word
*/
void printHuffmanWord(MAP_NODE *map);

/*
Gets input from the user about a list of binary numbers and decodes the numbers from the tree to
a word
*/
void decodeHuffmanWord(TREE_NODE* root);

/*
Gets the file name from the user and then encodes the file using the huffman tree

The file format has the first byte as the padding added at the end of the file, as to make sure
we fill up all 8 bits in the last byte.
*/
void encodeFile(MAP_NODE* map);

/*
Takes in a file encoded by encodeFile and decodes the file using the tree
*/
void decodeFile(TREE_NODE* root);

/*
Helper method that gets the corresponding bit from a char (byte)
*/
char getBitChar(char byte, int bit);

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
			printHuffmanWord(map);
			break;
		}
		case '6':
		{
			decodeHuffmanWord(root);
			break;
		}
		case '7':
		{
			encodeFile(map);
			break;
		}
		case '8':
		{
			decodeFile(root);
			break;
		}
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
		if (c < ASCII_START || c >= ASCII_END)
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

void printHuffmanWord(MAP_NODE* map)
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
}

void decodeHuffmanWord(TREE_NODE* root)
{
	printf("Enter an encoded word in binary: ");
	char word[MAX_INPUT_SIZE];
	TREE_NODE *node;
	char *strPtr = word;
	char printableChar[3];
	scanf("%100s", word);
	FLUSH;
	while (1)
	{
		int errCode = traverse_tree(root, strPtr, &node, &strPtr);
		if (errCode == TREE_TRAVERSAL_ERR)
		{
			printf("\nERROR: Wasn't able to finish traversal of tree with given string\n");
			break;
		}

		get_printable_char(node->data, printableChar);
		printf("%s", printableChar);

		if (errCode == TREE_TRAVERSAL_FINISHED)
		{
			break;
		}
	}
	printf("\n");
}

void encodeFile(MAP_NODE* map)
{
	char filename[MAX_INPUT_SIZE];

	printf("Enter the file name to encode ( 0 for default: %s ): ", DEFAULT_INPUT_FILE);
	scanf("%100s", filename);
	FLUSH;

	if (strcmp(filename, "0") == 0)
	{
		strcpy(filename, DEFAULT_INPUT_FILE);
	}

	FILE *fileToEncode = fopen(filename, "r");
	if (fileToEncode == NULL)
	{
		printf("Error opening file\n");
		return;
	}

	printf("Enter the out file ( 0 for default: %s ): ", DEFAULT_OUTPUT_FILE);
	scanf("%100s", filename);
	FLUSH;

	if (strcmp(filename, "0") == 0)
	{
		strcpy(filename, DEFAULT_OUTPUT_FILE);
	}

	FILE *fileOut = fopen(filename, "wb");
	if (fileOut == NULL)
	{
		printf("Error opening file\n");
		return;
	}

	char emptyByte = 0;
	fwrite(&emptyByte, sizeof(char), 1, fileOut); // save space in the first byte
	// we will later on use this first byte to write the amount of padding was added at the end

	char c;
	char binBuffer[9]; // 8 bits + 1 null terminator
	binBuffer[8] = '\0';
	int currVal = 0; // current pos in the binBuffer
	// we will keep loading the binBuffer until it is full, then use strtol base 2 to get the value (remember to cast down to 8 bits (char))
	while (fscanf(fileToEncode, "%c", &c) != EOF)
	{
		char *bin = get_map_node(map, c)->bin;
		for (int i = 0; i < strlen(bin); i++)
		{
			binBuffer[currVal] = bin[i];
			currVal++;
			if (currVal == 8)
			{
				char value = (char)strtol(binBuffer, NULL, 2);
				fwrite(&value, sizeof(char), 1, fileOut);
				currVal = 0;
			}
		}
	}

	if(currVal != 0)
	{
		char padding = 8 - currVal;
		// we need to pad the last byte with 0s
		for (int i = currVal; i < 8; i++)
		{
			binBuffer[i] = '0';
		}
		char value = (char)strtol(binBuffer, NULL, 2);
		fwrite(&value, sizeof(char), 1, fileOut);
		fseek(fileOut, 0, SEEK_SET);
		fwrite(&padding, sizeof(char), 1, fileOut);
	}

	printf("Successfully encoded file\n");

	fclose(fileToEncode);
	fclose(fileOut);
}

void decodeFile(TREE_NODE* root)
{
	char filename[MAX_INPUT_SIZE];

	printf("Enter the file name to decode ( 0 for default: %s ): ", DEFAULT_INPUT_FILE);
	scanf("%100s", filename);
	FLUSH;

	if (strcmp(filename, "0") == 0)
	{
		strcpy(filename, DEFAULT_INPUT_FILE);
	}

	FILE *encodedFile = fopen(filename, "rb");
	if (encodedFile == NULL)
	{
		printf("Error opening file\n");
		return;
	}

	printf("Enter the out file ( 0 for default: %s ): ", DEFAULT_OUTPUT_FILE);
	scanf("%100s", filename);
	FLUSH;

	if (strcmp(filename, "0") == 0)
	{
		strcpy(filename, DEFAULT_OUTPUT_FILE);
	}

	FILE *fileOut = fopen(filename, "w");
	if (fileOut == NULL)
	{
		printf("Error opening file\n");
		return;
	}

	char padding;
	fread(&padding, sizeof(char), 1, encodedFile);

	char curr_char, next_char; //we need to read one byte ahead of the byte we are processing as to be able to check when we hit our eof
	fread(&curr_char, sizeof(char), 1, encodedFile);
	TREE_NODE* iter = root;

	while(1)
	{
		if(fread(&next_char, sizeof(char), 1, encodedFile) == 0)
		{
			// we reached the eof, so this curr char will have padding
			for(int i = 0; i < 8-padding ; i++)
			{
				if(getBitChar(curr_char, i) == '1')
				{
					iter = iter->right;
				}
				else
				{
					iter = iter->left;
				}

				if(iter->data != EMPTY_TREE_NODE)
				{
					fprintf(fileOut, "%c", iter->data);
					iter = root;
				}
			}
			break;
		}
		else
		{
			// not at eof, read as normal
			for(int i = 0; i < 8; i++)
			{
				if(getBitChar(curr_char, i) == '1')
				{
					iter = iter->right;
				}
				else
				{
					iter = iter->left;
				}

				if(iter->data != EMPTY_TREE_NODE)
				{
					fprintf(fileOut, "%c", iter->data);
					iter = root;
				}
			}
			curr_char = next_char;
		}
	}

	if(iter != root)
	{
		printf("ERROR: File did not fully decode.\n");
	}
	else
	{
		printf("File decoded successfully.\n");
	}

	fclose(encodedFile);
	fclose(fileOut);
}

char getBitChar(char byte, int bit)
{
	bit = 7 - bit;

	if( ((byte >> bit) & 1) == 1)
	{
		return '1';
	}
	else
	{
		return '0';
	}
}
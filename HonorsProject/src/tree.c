#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tree.h"
#include "list.h"

TREE_NODE *tree_init(char data)
{
	TREE_NODE *tree = (TREE_NODE *)malloc(sizeof(TREE_NODE));
	tree->data = data;
	tree->weight = 0;
	tree->left = NULL;
	tree->right = NULL;

	return tree;
}

void get_printable_char(char data, char *toPrint)
{
	if (data == '\n')
	{
		strcpy(toPrint, "\\n");
	}
	else if (data == '\t')
	{
		strcpy(toPrint, "\\t");
	}
	else if (data == '\r')
	{
		strcpy(toPrint, "\\r");
	}
	else if (data == '\v')
	{
		strcpy(toPrint, "\\v");
	}
	else if (data == '\b')
	{
		strcpy(toPrint, "\\b");
	}
	else if (data == '\f')
	{
		strcpy(toPrint, "\\f");
	}
	else if (data == '\a')
	{
		strcpy(toPrint, "\\a");
	}
	else if (data == '\0')
	{
		strcpy(toPrint, "\\0");
	}
	else if(data == 27) // escape character
	{
		strcpy(toPrint, "\\e");
	}
	else
	{
		toPrint[0] = data;
		toPrint[1] = '\0';
	}
}

void tree_print(TREE_NODE *tree, int depth, int option)
{
	if (tree == NULL)
	{
		return;
	}
	tree_print(tree->right, depth + 1, option);

	char toPrint[3];
	get_printable_char(tree->data, toPrint);

	if (tree->data != EMPTY_TREE_NODE)
	{
		do
		{
			if (option == PRINT_OPTION_WEIGHTS_ONLY && tree->weight == 0)
			{
				break;
			}
			else if (option == PRINT_OPTION_CHARS_ONLY && tree->data < 32)
			{
				break;
			}
			for (int i = 0; i < depth; i++)
			{
				printf("  ");
			}

			printf("\'%s\' (DEC%d): Weight %d\n", toPrint, tree->data, tree->weight);

		} while (0);
	}

	tree_print(tree->left, depth + 1, option);
}

void init_map_recurse(MAP_NODE *map, TREE_NODE* tree, char* bin)
{
	if(!tree)
	{
		return;
	}

	if(tree->data != EMPTY_TREE_NODE)
	{
		map[(int)(tree->data)].data = tree->data;
		map[(int)(tree->data)].weight = tree->weight;
		strcpy(map[(int)(tree->data)].bin, bin);
	}

	int pos = strlen(bin);

	bin[pos] = '0';
	bin[pos + 1] = '\0';
	init_map_recurse(map, tree->left, bin);

	bin[pos] = '1';
	bin[pos + 1] = '\0';
	init_map_recurse(map, tree->right, bin);
}


MAP_NODE *map_init(TREE_NODE *tree)
{
	MAP_NODE *map = (MAP_NODE *)malloc(sizeof(MAP_NODE) * (ASCII_END));
	char binStr[BIN_MAX_STR];
	binStr[0] = '\0';

	init_map_recurse(map, tree, binStr);
	return map;
}

void map_print(MAP_NODE *map, int option)
{
	char printableChar[3];
	for(int i = ASCII_START; i < ASCII_END; i++)
	{
		if(option == PRINT_OPTION_WEIGHTS_ONLY && map[i].weight == 0)
		{
			continue;
		}
		else if(option == PRINT_OPTION_CHARS_ONLY && map[i].data < 32)
		{
			continue;
		}
		get_printable_char(map[i].data, printableChar);
		printf("\'%s\' (DEC%d): %s\n", printableChar, map[i].data, map[i].bin);
	}
}

MAP_NODE* get_map_node(MAP_NODE *map, char data)
{
	return &map[(int)(data)];
}

void print_char_weights(MAP_NODE *map)
{
	char printableChar[3];
	for(int i = ASCII_START; i < ASCII_END; i++)
	{
		if(map[i].weight > 0)
		{
			get_printable_char(map[i].data, printableChar);
			printf("\'%s\' (DEC%d): %d\n", printableChar, map[i].data, map[i].weight);
		}
	}
}

int traverse_tree(TREE_NODE *tree, char* bin, TREE_NODE** treeOut, char** binOut)
{
	char* strPtr = bin;
	TREE_NODE* treePtr = tree;
	while(1)
	{
		if(treePtr->data != EMPTY_TREE_NODE)
		{
			*treeOut = treePtr;
			*binOut = strPtr;

			if(*strPtr == '\0')
			{
				return TREE_TRAVERSAL_FINISHED; // finished traversing
			}

			return TREE_TRAVERSAL_FOUND; // found a node
		}

		if(*strPtr == '0')
		{
			treePtr = treePtr->left;
		}
		else if(*strPtr == '1')
		{
			treePtr = treePtr->right;
		}
		else
		{
			// we reached the end of the string or an invalid character
			return TREE_TRAVERSAL_ERR;
		}
		strPtr++;
	}

	// return TREE_TRAVERSAL_ERR; // this shouldn't ever be reached
}

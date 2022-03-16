#ifndef TREE_H
#define TREE_H

#define EMPTY_TREE_NODE 0
#define BIN_MAX_STR 200

/*
 * A node in the Huffman tree.
 */
typedef struct tree_node{
	struct tree_node* left;
	struct tree_node* right;
	char data;
	int weight;
} TREE_NODE;

/*
The map is used after the huffman tree is built to map characters to binary strings.
Helps in saving time when encoding / looking up the binary representation of characters.
*/
typedef struct map_node{
	char data;
	int weight;
	char bin[BIN_MAX_STR]; // binary representation of the data
} MAP_NODE;

/*
Inits a tree node with the given char data
*/
TREE_NODE* tree_init(char data);

/*
If the char passed in data is a special character (\n, \t, etc.), turns the character into a
"\n" and puts it in toPrint

toPrint is expected to be a length of 3
*/
void get_printable_char(char data, char* toPrint);

#define PRINT_OPTION_NONE 0 // prints everything
#define PRINT_OPTION_CHARS_ONLY 1 // only prints characters above DEC32
#define PRINT_OPTION_WEIGHTS_ONLY 2 // only prints characters with non-zero weights

/*
Prints the tree in a recursive fashion Right-Root-Left
*/
void tree_print(TREE_NODE* tree, int depth, int option);

/*
Inits a map with the given tree
*/
MAP_NODE *map_init(TREE_NODE *tree);
/*
Prints the map
*/
void map_print(MAP_NODE *map, int option);

/*
Given a character, returns the corresponding node in the map
*/
MAP_NODE* get_map_node(MAP_NODE *map, char data);

/*
Prints the non-zero weights of each characters in the map
*/
void print_char_weights(MAP_NODE *map);

#define TREE_TRAVERSAL_ERR -1 // error code for tree traversal
#define TREE_TRAVERSAL_FOUND 1 // found the char in the tree
#define TREE_TRAVERSAL_FINISHED 0 // found the char in the tree and finished traversing the whole bin string
/*
Given a binary string, traverses the tree and returns the corresponding node in the tree
binOut is the last position in the binary string that was traversed
*/
int traverse_tree(TREE_NODE *tree, char* bin, TREE_NODE** treeOut, char** binOut);

#endif
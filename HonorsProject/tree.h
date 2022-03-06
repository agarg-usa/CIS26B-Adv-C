#ifndef TREE_H
#define TREE_H

#define EMPTY_TREE_NODE 0
#define BIN_MAX_STR 200

typedef struct tree_node{
	struct tree_node* left;
	struct tree_node* right;
	char data;
	int weight;
} TREE_NODE;

typedef struct map_node{
	char data;
	int weight;
	char bin[BIN_MAX_STR]; // binary representation of the data
} MAP_NODE;


TREE_NODE* tree_init(char data);
void get_printable_char(char data, char* toPrint);

#define PRINT_OPTION_NONE 0
#define PRINT_OPTION_CHARS_ONLY 1
#define PRINT_OPTION_WEIGHTS_ONLY 2
void tree_print(TREE_NODE* tree, int depth, int option);

MAP_NODE *map_init(TREE_NODE *tree);
void map_print(MAP_NODE *map, int option);

MAP_NODE* get_map_node(MAP_NODE *map, char data);
void print_char_weights(MAP_NODE *map);

#endif
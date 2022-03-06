#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char id[5];
	char name[21];
	int qty;

	char buff[100];
	fgets(buff, 100, stdin);

	char *token = strtok(buff, ",");
	strncpy(id, token, 5);

	token = strtok(NULL, ":");
	strncpy(name, token, 21);

	token = strtok(NULL, "\n");
	qty = atoi(token);
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{

}

//example hash function for int
int hash(int key, int size)
{
	return key % size;
}

int hash(char* key, int size)
{
	int sum = 0;
	while(*key)
	{
		sum += *key;
		key++;
	}

	return sum % size;
}
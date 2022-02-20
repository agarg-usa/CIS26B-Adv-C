/*
CIS 26B - Advanced C Programming
Homework #3:
 Hashing to a file and using advanced string manipulation functions.

 This program allows additions to or displays of a database records.

 NAME: Aryan Garg
 IDE: Gcc

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>


#define FLUSH while (getchar() != '\n')

// Length of hardware identifiers
#define HRDWARE_ID_LEN 4

// Maximum length of hardware names.
#define MAX_HRDWARE_NAME_LEN 20

// Parameters for the database hashtable structure.
#define BUCKET_SIZE 3   // Number of records per hash bucket in the data file
#define NUM_BUCKETS 30  // Number of buckets in the file.

//  Structure with a hardware record, as it is stored in the database.
typedef struct {
  // id
  // name
  // qty;
  char id[HRDWARE_ID_LEN+1];
  char name[MAX_HRDWARE_NAME_LEN+1];
  int qty;
} HARDWARE;

/*
Returns the hash value for a given HARDWARE record.
*/
int hash(HARDWARE *hardware);
/*
Function for handling insert command.
*/
void insert(FILE* hashtable);
/*
Function for handling search command.
*/
void search(FILE* hashtable);
/*
Function for handling delete command.
*/
void delete(FILE* hashtable);
/*
Function for handling insert data from external file command
*/
void getFromExtFile(FILE* hashtable);
/*
Function that maintains the loop to get user input
*/
void inputLoop(FILE* hashtable);

/*
Given a hash and a bucket number, moves file to the offset of the bucket.
*/
void moveFilePointerToBucket(FILE* hashtable, int hash, int bucket);
/*
Given a hash and a bucket number, moves file to the offset of the bucket, and reads the buckets into out
*/
void getBuckets(FILE* hashtable, int hash, HARDWARE* out);

/*
Reads a hardware record from the given file stream
returns 1 if successful, else -1
*/
int readFromStream(FILE* stream, HARDWARE* out);

/*
Trims the whitespace from the beginning and end of a string
*/
char *trimwhitespace(char *str);

/*
prints the given hardware record
*/
void printHardware(HARDWARE* hardware);

/*
Dumps the hashtable (used for debugging)
*/
void dumpHashtable(FILE* hashtable);

int main(int argc, char** argv) {

	char filename[100];
	FILE* hashtableFile;

	if(argc > 1) {
		strncpy(filename, argv[1], 100);
	} else {
		strcpy(filename, "hardware.dat");
	}

	hashtableFile = fopen(filename, "r+b");
	if(!hashtableFile) // file doesnt exist
	{
		hashtableFile = fopen(filename, "w+b");
		if(!hashtableFile) {
			printf("Could not open %s.\n", filename);
			exit(1);
		}

		printf("File %s not found. Writing with new data\n", filename);

		// Initialize the file to all zero bytes.
		HARDWARE emptyHardware = {0};
		for(int i = 0; i < NUM_BUCKETS*BUCKET_SIZE; i++) {
			fwrite(&emptyHardware, sizeof(HARDWARE), 1, hashtableFile);
		}
	}

	inputLoop(hashtableFile);
	// dumpHashtable(hashtableFile);
	fclose(hashtableFile);
    return 0;
}

void inputLoop(FILE* hashtable)
{
	char menu[] = "\nPlease choose an option:\n"
	" (S) Search\n"
	" (D) Delete\n"
	" (I) Insert\n"
	" (B) Insert data from external file\n"
	" (E) Exit\n";

	while(1)
	{
		puts(menu);
		char choice;
		scanf("%c", &choice);
		FLUSH;
		switch(choice)
		{
			case 'S':
			case 's':
				search(hashtable);
				break;
			case 'D':
			case 'd':
				delete(hashtable);
				break;
			case 'I':
			case 'i':
				insert(hashtable);
				break;
			case 'B':
			case 'b':
				getFromExtFile(hashtable);
				break;
			case 'E':
			case 'e':
				return;
			default:
				printf("Invalid choice.\n");
		}
	}

}

int hash(HARDWARE *hardware) {
	int key = 0;
	int i;
	for(i = 0; i < HRDWARE_ID_LEN; i++) {
		key += hardware->id[i]*hardware->id[i]*hardware->id[i];
	}
	return key % NUM_BUCKETS;
}

void moveFilePointerToBucket(FILE* hashtable, int hash, int bucket)
{
	fseek(hashtable, hash*sizeof(HARDWARE)*BUCKET_SIZE + bucket*sizeof(HARDWARE), SEEK_SET);
}

/**
 * Given a hash, puts all the buckets into the out array.
 */
void getBuckets(FILE* hashtable, int hash, HARDWARE* out)
{
	moveFilePointerToBucket(hashtable, hash, 0);
	fread(out, sizeof(HARDWARE), 3, hashtable);
}

int insertIntoTable(FILE* hashtable, HARDWARE* hardware)
{
	int hashNum = hash(hardware);
	HARDWARE buckets[BUCKET_SIZE];
	getBuckets(hashtable, hashNum, buckets);
	int emptyBucket = -1;
	for(int i = 0; i < BUCKET_SIZE; i++)
	{
		if(buckets[i].id[0] == '\0')
		{
			emptyBucket = i;
			// dont break here because we still need to compare the rest of the buckets to see if this is a duplicate or not
		}
		else if(strcmp(buckets[i].id, hardware->id) == 0) //bucket already contains this hardware
		{
			return -1;
		}
	}

	moveFilePointerToBucket(hashtable, hashNum, emptyBucket);
	fwrite(hardware, sizeof(HARDWARE), 1, hashtable);
	return 0;
}

char *trimwhitespace(char *str)
// code taken from SO https://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}

void printHardware(HARDWARE* hardware)
{
	printf("ID: %s Name: %s Qty: %d Hash: %d\n", hardware->id, hardware->name, hardware->qty, hash(hardware));
}

int readFromStream(FILE* stream, HARDWARE* out)
{
	char buff[100];
	fgets(buff, 100, stream);

	char *token = trimwhitespace(strtok(buff, ","));

	if(strlen(token) != HRDWARE_ID_LEN)
	{
		return -1;
	}
	strncpy(out->id, token, HRDWARE_ID_LEN+1);

	token = trimwhitespace(strtok(NULL, ":"));

	if(strlen(token) > MAX_HRDWARE_NAME_LEN)
	{
		return -1;
	}

	strncpy(out->name, token, MAX_HRDWARE_NAME_LEN+1);

	token = trimwhitespace(strtok(NULL, "\n"));

	if(token == NULL)
	{
		return -1;
	}

	char* endPtr; // used to check if the string is a number
	out->qty = strtol(token, &endPtr, 10);

	if(*endPtr != '\0' || errno == ERANGE)
	{
		return -1;
	}

	// check if hardware id is all numbers
	for(int i = 0; i < HRDWARE_ID_LEN; i++)
	{
		if(!isdigit(out->id[i]))
		{
			return -1;
		}
	}

	// check if hardware name is all letters, spaces, or parentheses
	for(int i = 0; i < MAX_HRDWARE_NAME_LEN && out->name[i] != '\0'; i++)
	{
		if(!isalnum(out->name[i]) && out->name[i] != ' ' && out->name[i] != '(' && out->name[i] != ')')
		{
			return -1;
		}

		// save as uppercase
		out->name[i] = toupper(out->name[i]);
	}

	return 1;
}

void insert(FILE* hashtable)
{
	puts("Please enter the new hardware:");
	HARDWARE hardware;
	if(readFromStream(stdin, &hardware) == -1)
	{
		puts("Invalid hardware. Please try again.\n");
		return;
	}

	if(insertIntoTable(hashtable, &hardware) == -1)
	{
		puts("Hardware ID already exists.\n");
	}
	else
	{
		puts("Hardware successfully inserted.");
		printHardware(&hardware);
	}
}


void search(FILE* hashtable)
{
	puts("Please enter the hardware id:");
	char id[HRDWARE_ID_LEN+1];
	scanf("%4s", id);
	FLUSH;

	HARDWARE hardwareSearch;
	strcpy(hardwareSearch.id, id);
	int hashNum = hash(&hardwareSearch);

	HARDWARE buckets[BUCKET_SIZE];
	getBuckets(hashtable, hashNum, buckets);

	for(int i = 0; i < BUCKET_SIZE; i++)
	{
		if(strcmp(buckets[i].id, id) == 0)
		{
			puts("Hardware found.");
			printHardware(&buckets[i]);
			return;
		}
	}

	puts("Hardware not found.\n");
}

void delete(FILE* hashtable)
{
	puts("Please enter the hardware id:");
	char id[HRDWARE_ID_LEN+1];
	scanf("%4s", id);
	FLUSH;

	HARDWARE hardwareSearch;
	strcpy(hardwareSearch.id, id);
	int hashNum = hash(&hardwareSearch);

	HARDWARE buckets[BUCKET_SIZE];
	getBuckets(hashtable, hashNum, buckets);

	for(int i = 0; i < BUCKET_SIZE; i++)
	{
		if(strcmp(buckets[i].id, id) == 0)
		{
			puts("Hardware Deleted.");
			printHardware(&buckets[i]);

			moveFilePointerToBucket(hashtable, hashNum, i);
			HARDWARE emptyHardware = {0};
			fwrite(&emptyHardware, sizeof(HARDWARE), 1, hashtable);
			return;
		}
	}

	puts("Hardware not found.\n");
}

void getFromExtFile(FILE* hashtable)
{
	puts("Please enter a file name");
	char fileName[100];
	scanf("%100s", fileName);
	FLUSH;

	FILE* file = fopen(fileName, "r");
	if(file == NULL)
	{
		puts("File not found.\n");
		return;
	}

	HARDWARE hardware;
	while(!feof(file))
	{
		if(readFromStream(file, &hardware) == -1)
		{
			puts("Invalid hardware. Please try again.\n");
			continue;
		}

		if(insertIntoTable(hashtable, &hardware) == -1)
		{
			puts("Hardware ID already exists.\n");
		}
		else
		{
			puts("Hardware successfully inserted.");
			printHardware(&hardware);
		}
	}

}

void dumpHashtable(FILE* hashtable)
{
	HARDWARE buckets[BUCKET_SIZE];
	for(int i = 0; i < NUM_BUCKETS; i++)
	{
		getBuckets(hashtable, i, buckets);
		for(int j = 0; j < BUCKET_SIZE; j++)
		{
			if(buckets[j].id[0] != '\0')
			{
				printHardware(&buckets[j]);
			}
		}
	}
}



/*
SAMPLE OUTPUT 1


File hardware.dat not found. Writing with new data

Please choose an option:
 (S) Search
 (D) Delete
 (I) Insert
 (B) Insert data from external file
 (E) Exit

S
Please enter the hardware id:
1234
Hardware not found.


Please choose an option:
 (S) Search
 (D) Delete
 (I) Insert
 (B) Insert data from external file
 (E) Exit

B
Please enter a file name
jan_hw.txt
Hardware successfully inserted.
ID: 6745 Name: MOLLY BOLT Qty: 57 Hash: 4
Hardware successfully inserted.
ID: 5675 Name: SCREW DRIVER Qty: 199 Hash: 23
Hardware successfully inserted.
ID: 1235 Name: WIDGET Qty: 28 Hash: 17
Hardware successfully inserted.
ID: 2341 Name: WING NUT Qty: 89 Hash: 28
Hardware successfully inserted.
ID: 8624 Name: SLEDGE HAMMER Qty: 27 Hash: 8
Hardware successfully inserted.
ID: 9162 Name: FLASH LIGHT Qty: 25 Hash: 6
Hardware successfully inserted.
ID: 7146 Name: CEMENT BAGS Qty: 113 Hash: 6
Hardware successfully inserted.
ID: 2358 Name: VISE Qty: 44 Hash: 24
Hardware successfully inserted.
ID: 1622 Name: HAMMER Qty: 15 Hash: 23
Hardware successfully inserted.
ID: 1832 Name: THERMOSTAT Qty: 78 Hash: 26
Hardware successfully inserted.
ID: 3271 Name: NAIL Qty: 2345 Hash: 25
Hardware successfully inserted.
ID: 4717 Name: BRACE Qty: 234 Hash: 7

Please choose an option:
 (S) Search
 (D) Delete
 (I) Insert
 (B) Insert data from external file
 (E) Exit

S
Please enter the hardware id:
1622
Hardware found.
ID: 1622 Name: HAMMER Qty: 15 Hash: 23

Please choose an option:
 (S) Search
 (D) Delete
 (I) Insert
 (B) Insert data from external file
 (E) Exit

D
Please enter the hardware id:
1622
Hardware Deleted.
ID: 1622 Name: HAMMER Qty: 15 Hash: 23

Please choose an option:
 (S) Search
 (D) Delete
 (I) Insert
 (B) Insert data from external file
 (E) Exit

S
Please enter the hardware id:
1622
Hardware not found.


Please choose an option:
 (S) Search
 (D) Delete
 (I) Insert
 (B) Insert data from external file
 (E) Exit

I
Please enter the new hardware:
1622, Wrench : 654
Hardware successfully inserted.
ID: 1622 Name: WRENCH Qty: 654 Hash: 23

Please choose an option:
 (S) Search
 (D) Delete
 (I) Insert
 (B) Insert data from external file
 (E) Exit
E

*/


/*
  New session to test input errors when inserting one record from the keyboard

Examples of invalid input:

9162 Flash Light:25 // missing ‘,’ after ID
9162,Flash Light 25 // missing ‘:’ after name
91A2 Flash Light:25 // invalid ID – digits only
91-2 Flash Light:25 // invalid ID – digits only
5392,BOLT [REGULAR]:1311 // invalid name – [ ] not allowed
5392,BOLT (REGU1AR):1311 // invalid name – digits not allowed
9162,Flash Light:2A      // invalid quantity
9162,Flash Light:        // incomplete input line

Please choose an option:
 (S) Search
 (D) Delete
 (I) Insert
 (B) Insert data from external file
 (E) Exit

kjaspduf9asdjfasd
Invalid choice.

Please choose an option:
 (S) Search
 (D) Delete
 (I) Insert
 (B) Insert data from external file
 (E) Exit

I
Please enter the new hardware:
9162 Flash Light:25
Invalid hardware. Please try again.


Please choose an option:
 (S) Search
 (D) Delete
 (I) Insert
 (B) Insert data from external file
 (E) Exit

I
Please enter the new hardware:
9162,Flash Light:2A
Invalid hardware. Please try again.


Please choose an option:
 (S) Search
 (D) Delete
 (I) Insert
 (B) Insert data from external file
 (E) Exit

I
Please enter the new hardware:
5392,BOLT [REGULAR]:1311
Invalid hardware. Please try again.


Please choose an option:
 (S) Search
 (D) Delete
 (I) Insert
 (B) Insert data from external file
 (E) Exit

I
Please enter the new hardware:
91A2 Flash Light:25
Invalid hardware. Please try again.


Please choose an option:
 (S) Search
 (D) Delete
 (I) Insert
 (B) Insert data from external file
 (E) Exit

E
*/

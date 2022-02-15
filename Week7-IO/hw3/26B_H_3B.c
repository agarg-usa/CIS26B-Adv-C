/*
CIS 26B - Advanced C Programming
Homework #3: 
 Hashing to a file and using advanced string manipulation functions.
 
 This program allows additions to or displays of a database records.

 NAME:
 IDE:
 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
} HARDWARE;

int main(int argc, char** argv) {
    
    return 0;
}

/*
You can see that you are adding or looking up records in a HASHED FILE.
When adding records from a file, the program will prompt a user for
a filename which has records that look like this:

9524,CLAMP:523
1524,SANDER:99
5219,SAW:211

You will do batch insertions into the hashed file. Treat overflows in a
bucket as an unresolvable problem but report the error. The hash key is
the id and you should sum the cube of the ASCII values of the characters
making up the id before modding by size to find the bucket to put the record.

When inserting one record from the keyboard, the user should enter on one line
 id, name:qty
with any amount of whitespace around the two tokens. It is a major task to parse,
case, and space the requested data so that it agrees with your format in the
hashed file.  Don't worry about the characters they enter for the name.
Just give a "Not Found" type of error if they enter something that is
obviously crazy.

*/

/*
You must follow all the rules for good token parsing!!
Run the program at least twice.
Duplicate id not allowed!!!
 
Examples (this output is incomplete):

 Enter selection: s
 Enter id: 6745
 6745 found at hash bucket 4.
 Name: MOLLY BOLT
 Quantity: 5

 Enter selection: d
 Enter id: 6745
 6745 deleted.

 Enter selection: s
 Enter id: 6745
 6745 : not found.

 Enter selection: i
 Enter a hardware id, name, and quantity:
 1269   ,  Flash Light     :    25

 Enter selection: s
 Enter id: 1269
 1269 found at hash bucket 4.
 Name: FLASH LIGHT
 Quantity: 25

 Enter selection: i
 Enter a hardware id, name, and quantity:
 9621, hi : 4
 All buckets are full!
 9621 rejected!

 Enter selection: q

 
 Enter selection:    4
 Illegal menu selection!  Try again!

 Enter selection:   2 foo
 Legal entry has one menu selection only!

 Enter selection:   B

 Enter filename:    foobar.foobar
 Batch insertion file could not be opened!

 Enter selection: B

 Enter filename:    asg3.txt
 Bucket overflow! Record for 9621 rejected!

 Enter selection:   I
 Enter a hardware id, name, and quantity:
 1832   ,    THERMOstat  :    78
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
*/

/*
 Suggestion: Display the menu before the loop.
 Within the loop, display the menu upon request (prompt the user to enter
 an option from the menu, or M to display the menu):
 
 Enter selection (M - menu):
 
 */

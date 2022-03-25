/*
   Task 2:

   This program is a collection of unrelated questions / functions.

REQUIREMENTS:
   A. Finish the definition of the showTimeStamp() function
   B. What is the strGuess() function's task? Write your answer as a comment above the function's definition.
   C. Write code in main() to call the bitGuess() function and provide some output.
      What is the bitGuess() function's task? Write your answer as a comment above the function's definition.
      What is the bitHelper() function's task? Write your answer as a comment above the function's definition.
   D. Write the definition of the decrypt function.
   E. Find and fix errors in run_tests().

   -> Run the program.
   -> Save the output as a comment at the end of the source file.
   -> Write your name and IDE below

 NAME: Aryan Garg
 IDE: VSCode / GCC
*~*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

//  strcut definition used in SECTION E
struct test
{
    int arg;              // an integer to be used as argument for function
    int (*function)(int); // a function pointer
    char name[16];        // function's name
};

int strGuess(const char *d, const char *s);
void showTimeStamp(void);

int main (void)
{
// SECTION A: working with time functions
    showTimeStamp();

// SECTION B: Testing the strGuess() function
    char s1[32] = "Programming in Java";
    char s2[32] = "Programming in Python";

    printf( "%d \n", strGuess(s1, s2));
    printf( "%d \n", strGuess(s2, s1));

// SECTION C: Testing the bitGuess() function

	int bitGuess(unsigned short, unsigned short);

	int bitGuessTest1 = 0xFF;
	int bitGuessTest2 = 0xF0;

	printf("Bitguess for %d and %d returns %d\n", bitGuessTest1, bitGuessTest2, bitGuess(bitGuessTest1, bitGuessTest2)); // should print 0

	bitGuessTest1 = 0x0F;

	printf("Bitguess for %d and %d returns %d\n", bitGuessTest1, bitGuessTest2, bitGuess(bitGuessTest1, bitGuessTest2)); // should print 1


//  SECTION D: bit manipulation
    void decrypt(const char key[], const char ent[], char det[]);
    char key[] = "Advanced C";
    char ent[100] = "8023.)/<)423}2;}%>1(.4+8}};2/}<)<}3>/$-)423}<39}8>/$-)423s";
    char det[100];

    decrypt(key, ent, det);
    printf("%s\n%s\n", ent, det);

//  SECTION E
    void run_tests(int n, ...); // incomplete declaration
    int f1(int);
    int f2(int);
    int f3(int);
    int f4(int);

    struct test t1 = { 15, f1, "f1"};
    struct test t2 = { 25, f2, "f2"};
    struct test t3 = { 19, f3, "f3"};
    struct test t4 = { 17, f4, "f4"};
    run_tests(1, &t1, &t2, NULL); // 1st call
    run_tests(1, &t3, NULL);      // 2st call
    run_tests(1, &t1, &t4, NULL); // 1st call
    return 0;
}

/*~*~*~*~*~*~ Part A
   This function displays the current date and time
   using a format of your choice
*~*/
void showTimeStamp()
{
    printf("This is the showTimeStamp() function: \n");
	time_t t = time(NULL);
	char* chtime;
	chtime = ctime(&t);

	printf("The time is: %s\n", chtime);
}

/*~*~*~*~*~*~ Part B
   Describe the purpose of strGuess function below:
	this function is like a strcmp function. It compares the two strings then returns 0 if they are equal, otherwise
	returns the difference between the first found different char.
 *~*/
int strGuess(const char *d, const char *s)
{
   while (*d  &&  *s  &&  *d == *s)
       d++, s++;
   return *d - *s;
}

/*~*~*~*~*~*~ Part C
  Describe the purpose of bitHelper function below:

	returns the amount of 1's in the binary representation of the number.


*~*/
int bitHelper( unsigned short n )
{
    int c = 0;
    while ( n )
    {
       c += n & 1;
       n = n >> 1;
    }

    return c;
}

/*~*~*~*~*~*~ Part C
  Describe the purpose of bitGuess function below:

	this function returns true if n1 has the same amount of 1s in its binary representation as n2
	otherwise returns false
*~*/
int bitGuess( unsigned short n1, unsigned short n2 )
{
    return bitHelper(n1) == bitHelper(n2);
}

/*~*~*~*~*~*~ Part D
   One of the bitwise operators has been used to encrypt a string
   one character at a time using all characters in the encryption key,
   from left to right.
   Given the encryption key and ent[] the encrypted text, the decrypt
   function retrieves the original text and places it in det[].
*~*/
void decrypt(const char key[], const char ent[], char det[])
{
	for(int i = 0; i < strlen(ent); i++)
	{
		det[i] = ent[i];
		for(int j = 0; j < strlen(key); j++)
		{
			det[i] = det[i] ^ key[j];
		}
	}
}

/*~*~*~*~*~*~ Part E
The run_tests function has an unknown number of struct test * arguments.
The last argument is NULL and it is used as a sentinel value.
The purpose of the run_tests function is to call each function in its
argument list and display its value, name, and argument.
Use the int in each struct test as the argument to this function.
*~*/

void run_tests(int n, ...)
{
    va_list argp;
    int val;
    struct test* tp;

    va_start(argp, n);
    while( (tp = va_arg(argp, struct test *)) )
    {
        val = tp->function(tp->arg);
        printf("%s(%d) = %d\n", tp->name, tp->arg, val);
    }

}
// function to be tested by run_tests
int f1(int x)
{
    return 10 * x;
}
// function to be tested by run_tests
int f2(int x)
{
    return 3 * x;
}
// function to be tested by run_tests
int f3(int x)
{
    return x / 2;
}
// function to be tested by run_tests
int f4(int x)
{
    return x % 3;
}
/*~*~*~*~*~*~ Save the output below

This is the showTimeStamp() function:
The time is: Tue Mar 22 20:14:50 2022

-6
6
Bitguess for 255 and 240 returns 0
Bitguess for 15 and 240 returns 1
8023.)/<)423}2;}%>1(.4+8}};2/}<)<}3>/$-)423}<39}8>/$-)423s
Demonstration of Exclusive OR for Data Encryption and Decryption.����
f1(15) = 150
f2(25) = 75
f3(19) = 9
f1(15) = 150
f4(17) = 2

*~*/



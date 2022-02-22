/*
  CIS 26B - Advanced C Programming
  Homework 4:
  Bit Manipulation
  
  Computer Controlled Lights

  NAME:
  IDE:
  
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int  testbit(unsigned short wrd, int bit_to_test);
void printbits(unsigned short wrd);

int main( void )
{



    return 0;
}

/* *************************************************************
 Return 1 if bit_to_test is set and 0 if it is unset
 */
int  testbit(unsigned short wrd, int bit_to_test)
{
    wrd >>= bit_to_test;
    wrd &= 1;
    return wrd;
}

/* *************************************************************
 This uses a trick to print an unsigned short as a string of
 16 bits
 
 FIX ME: Update this function to display the string of 16 bits
 using the following pattern:
 11111 111111 11111
  (5)   (6)    (5)
 */
void printbits(unsigned short wrd)
{
    int  testbit(unsigned short wrd, int bit_to_test);
    int i;
    
    for (i = 15; i >= 0; i--)
    {
        printf("%1d", testbit(wrd, i));
        if (!(i % 4))
            printf(" ");
    }
    printf("\n");
}

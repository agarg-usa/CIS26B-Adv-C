/*
 Biwise Operators

 1. Define and use a macro to turn on a range of bits
 2. Define and use a macro to turn off a range of bits
 3. Define and use a macro to toggle a range of bits
 4. Write a function that takes an unsigned short parameter and returns an unsigned short
 with the bits in the parameter turned backwards (reversed).
 Thus, if the parameter has a binary value of
 11111111111100000000000000000011
 your function will return a value whose binary representation is
 11000000000000000000111111111111

 NAME: Aryan Garg
 IDE: GCC / VSCode
 */

#include <stdio.h>

int  testbit(unsigned short wrd, int bit_to_test);
void printbits(unsigned short wrd);
unsigned short reversebits(unsigned short wrd);

#define ON(bin, startbit, numbits) ( bin | ((~(((unsigned short)~0) << numbits)) << startbit) )
#define OFF(bin, startbit, numbits) ( (bin & ~((~(((unsigned short) ~0) << numbits)) << startbit)))
#define TOGGLE(bin, startbit, numbits) ( bin ^ ( ( ~( ((unsigned short)~0) << numbits) ) << startbit) )

int main (void)
{
    unsigned short wrd = 65, a = 32, b;
    int numbits = 3;
    int startbit = 2;

    printbits(wrd);

    // replace this with a macro with arguments
    // mask = (~(((unsigned short)~0) << numbits)) << startbit;
    b = ON(a, startbit, numbits);
    printf("Turn ON %d bits starting at bit#%d\n", numbits, startbit);
    printf("%d\n", a);
    printbits(a);
    printbits(b);
    printf("%d\n", b);

    a = 31;
    // replace this with a macro with arguments
    // mask = ~((~(((unsigned short) ~0) << numbits)) << startbit);
    b = OFF(a, startbit, numbits);
    printf("Turn OFF %d bits starting at bit#%d\n", numbits, startbit);
    printf("%d\n", a);
    printbits(a);
    printbits(b);
    printf("%d\n", b);

    a = 85;
    // mask = ??? // define this mask as a macro with arguments
	//((unsigned short)~0) creates 1111 1111 1111 1111
	// shift it left by numbits 1111 1111 1111 1000
	// not: 0000 0000 0000 0111
	// shift left by startbit 0000 0000 0001 1100
	// gives us the mask to ^

	// mask = ( ( ~( ((unsigned short)~0) << numbits) ) << startbit);
	b = TOGGLE(a, startbit, numbits);

    printf("Toggle %d bits starting at bit#%d\n", numbits, startbit);
    printf("%d\n", a);
    printbits(a);
    printbits(b);
    printf("%d\n", b);

	printf("Reveresing bits\n");
	printf("%d\n", a);
    printbits(a);
    printbits(reversebits(a));
    printf("%d\n", reversebits(a));

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

unsigned short reversebits(unsigned short wrd)
{
	unsigned short result = 0;

	for (int i = 0; i < 15; i++)
	{
		result |= wrd & 1;
		wrd >>= 1;
		result <<= 1;
	}
	result |= wrd & 1;
	return result;
}

/*

0000 0000 0100 0001
Turn ON 3 bits starting at bit#2
32
0000 0000 0010 0000
0000 0000 0011 1100
60
Turn OFF 3 bits starting at bit#2
31
0000 0000 0001 1111 
0000 0000 0000 0011
3
Toggle 3 bits starting at bit#2
85
0000 0000 0101 0101
0000 0000 0100 1001
73
Reveresing bits
85
0000 0000 0101 0101
1010 1010 0000 0000
43520
*/
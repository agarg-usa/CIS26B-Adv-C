#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	unsigned char a = 0;
	unsigned char b;
	b = ~a; // not
	printf("%ud\n", b);
	a = 0x0F;
	b = a & b; // and
	b = a | b; // or
	b = a ^ b; // xor
	// precedence : not and xor or
	a = 1;
	a = a << 1; // left shift, a *= 2
	a = a >> 1; // right shift, a /= 2
	a |= 0x0F; // or equals

	// we can print bits one at a time
	// for example
	b = a & 1;
	// bit 0 is b
	a >>= 1;
	b = a & 1;
	// bit 1 is b

	// we can also build masks by using bit shifts and bitwise functions
	// remember, if you << or >> you will push in 0s
	// you can use these masks to turn off / on / toggle  bits for example

	// to rotate bits you need to move the left bits and or them with the moved right bits

	// and good for turning on bits
	// or good for turning off bits
	// xor good for toggling bits
}
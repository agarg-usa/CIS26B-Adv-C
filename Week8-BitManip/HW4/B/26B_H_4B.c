/*
  CIS 26B - Advanced C Programming
  Homework 4:
  Bit Manipulation

  Computer Controlled Lights

  NAME: Aryan Garg
  IDE: GCC/ VSCode

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FLUSH while (getchar() != '\n')

int  testbit(unsigned short wrd, int bit_to_test);
void printbits(unsigned short wrd);
void overlayPattern(unsigned short *wrd);

int main( void )
{
	char menu[] = "MENU:\n1) turn on all lights\n"
	"2) turn on center stage lights (lights 5-10)\n"
	"3) turn on left stage lights (lights 11-15)\n"
	"4) turn on right stage lights (lights 0-4)\n"
	"5) turn off all lights\n"
	"6) turn off center stage lights\n"
	"7) turn off left stage lights\n"
	"8) turn off right stage lights\n"
	"9) overlay on/off pattern onto light configuration\n"
	"10) quit the menu\n";

	int choice;
	unsigned short lights = 0;

	while(1)
	{
		puts("\nCurrent setup of lights:");
		printbits(lights);
		puts(menu);
		printf("Enter your choice: ");
		choice = 0;
		scanf("%d", &choice);
		FLUSH;

		switch(choice)
		{
			case 1:
				lights = 0xFFFF;
				break;
			case 2:
				lights |= 0x07E0;
				break;
			case 3:
				lights |= 0xF800;
				break;
			case 4:
				lights |= 0x001F;
				break;
			case 5:
				lights = 0;
				break;
			case 6:
				lights &= 0b1111100000011111;
				break;
			case 7:
				lights &= 0b0000011111111111;
				break;
			case 8:
				lights &= 0b1111111111100000;
				break;
			case 9:
				overlayPattern(&lights);
				break;
			case 10:
				exit(0);
			default:
				puts("Invalid choice. Try again.");
		}

	}

	puts(menu);
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

/**
 * given a light config, gets input from user and overlays a pattern onto the light
 */
void overlayPattern(unsigned short *lights)
{
	puts("\nOverlay on/off pattern onto light configuration (Pattern, startBit):");
	char line[20];
	fgets(line, 20, stdin);
	if(strlen(line) > 1)
	{
		char* patternStr = strtok(line, " \n\t");
		char* startBitStr = strtok(NULL, " \n\t");

		char* endPtr;
		int startBit = strtol(startBitStr, &endPtr, 10);
		if(*endPtr != '\0' || startBit < 0 || startBit > 15)
		{
			puts("Invalid input. Try again.");
			return;
		}
		strtol(patternStr, &endPtr, 2);
		if(*endPtr != '\0' || strlen(patternStr) > 16)
		{
			puts("Invalid input. Try again.");
			return;
		}

		unsigned short ans = 0;

		for(int i = 0; i < 16; i++)
		{
			if(i >= startBit && i < startBit + strlen(patternStr))
			{
				ans |= (patternStr[ strlen(patternStr) - 1 - (i - startBit) ] - '0') << i;
			}
			else
			{
				ans |= testbit(*lights, i) << i;
			}
		}

		*lights = ans;
	}
	else
	{
		puts("Invalid input. Try again.");
		return;
	}
}

/*
Current setup of lights:
0000 0000 0000 0000
MENU:
1) turn on all lights
2) turn on center stage lights (lights 5-10)
3) turn on left stage lights (lights 11-15)
4) turn on right stage lights (lights 0-4)
5) turn off all lights
6) turn off center stage lights
7) turn off left stage lights
8) turn off right stage lights
9) overlay on/off pattern onto light configuration
10) quit the menu

Enter your choice: 1

Current setup of lights:
1111 1111 1111 1111
MENU:
1) turn on all lights
2) turn on center stage lights (lights 5-10)
3) turn on left stage lights (lights 11-15)
4) turn on right stage lights (lights 0-4)
5) turn off all lights
6) turn off center stage lights
7) turn off left stage lights
8) turn off right stage lights
9) overlay on/off pattern onto light configuration
10) quit the menu

Enter your choice: 7

Current setup of lights:
0000 0111 1111 1111
MENU:
1) turn on all lights
2) turn on center stage lights (lights 5-10)
3) turn on left stage lights (lights 11-15)
4) turn on right stage lights (lights 0-4)
5) turn off all lights
6) turn off center stage lights
7) turn off left stage lights
8) turn off right stage lights
9) overlay on/off pattern onto light configuration
10) quit the menu

Enter your choice: 9

Overlay on/off pattern onto light configuration (Pattern, startBit):
1011 3

Current setup of lights:
0000 0111 1101 1111
MENU:
1) turn on all lights
2) turn on center stage lights (lights 5-10)
3) turn on left stage lights (lights 11-15)
4) turn on right stage lights (lights 0-4)
5) turn off all lights
6) turn off center stage lights
7) turn off left stage lights
8) turn off right stage lights
9) overlay on/off pattern onto light configuration
10) quit the menu

Enter your choice: 10
*/

/*
Current setup of lights:
0000 0000 0000 0000
MENU:
1) turn on all lights
2) turn on center stage lights (lights 5-10)
3) turn on left stage lights (lights 11-15)
4) turn on right stage lights (lights 0-4)
5) turn off all lights
6) turn off center stage lights
7) turn off left stage lights
8) turn off right stage lights
9) overlay on/off pattern onto light configuration
10) quit the menu

Enter your choice: 9

Overlay on/off pattern onto light configuration (Pattern, startBit):
asdf 54
Invalid input. Try again.

Current setup of lights:
0000 0000 0000 0000
MENU:
1) turn on all lights
2) turn on center stage lights (lights 5-10)
3) turn on left stage lights (lights 11-15)
4) turn on right stage lights (lights 0-4)
5) turn off all lights
6) turn off center stage lights
7) turn off left stage lights
8) turn off right stage lights
9) overlay on/off pattern onto light configuration
10) quit the menu

Enter your choice: 9

Overlay on/off pattern onto light configuration (Pattern, startBit):
1011 66
Invalid input. Try again.

Current setup of lights:
0000 0000 0000 0000
MENU:
1) turn on all lights
2) turn on center stage lights (lights 5-10)
3) turn on left stage lights (lights 11-15)
4) turn on right stage lights (lights 0-4)
5) turn off all lights
6) turn off center stage lights
7) turn off left stage lights
8) turn off right stage lights
9) overlay on/off pattern onto light configuration
10) quit the menu

Enter your choice: asdf
Invalid choice. Try again.

Current setup of lights:
0000 0000 0000 0000
MENU:
1) turn on all lights
2) turn on center stage lights (lights 5-10)
3) turn on left stage lights (lights 11-15)
4) turn on right stage lights (lights 0-4)
5) turn off all lights
6) turn off center stage lights
7) turn off left stage lights
8) turn off right stage lights
9) overlay on/off pattern onto light configuration
10) quit the menu

Enter your choice: 10
*/
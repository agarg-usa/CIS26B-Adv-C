#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	printf("Hello, World!\n");

	char grade = 'A';
	printf("%c\n", grade);
	printf("%d\n", grade);

	int score = 100;
	short int age = 25;
	long int ssn = 11111111111L;
	unsigned int pin = 1234;

	printf("%d\n", score);
	printf("%hd\n", age);
	printf("%ld\n", ssn);
	printf("%u\n", pin);

	int a = -5;
	int b = 25;

	printf("%+d %+d\n", a, b); // includes sign

	printf("%5d %5d\n", a, b); // aligns left by a minimum of 5 spaces
	// "   -5"

	printf("%-5d %-5d\n", a, b); // aligns right by a minimum of 5 spaces
	//"-5   "

	printf("%05d %05d\n", a, b); // aligns left by 5, and adds 0's if necessary

	float doubleX = 3.14159;
	double doubleY = 234.3223;
	//float is 32 bits, double is 64 bits

	printf("%f %f\n", doubleX, doubleY);

	printf("%4.1f\n", doubleX); // min of 4 spaces, 1 decimal place
	//number gets rounded, not truncated


	//reading input

	char gradeInput;
	printf("Enter a grade: ");
	scanf("%c", &gradeInput); //&gradeInput returns pointer of gradeInput

	float gpaInput;
	printf("Enter your GPA: ");
	scanf("%f", &gpaInput); //%f for float

	double priceInput;
	printf("Enter a price: ");
	scanf("%lf", &priceInput); //%lf for double


	char firstCharI;
	char secondCharI;
	int randomIntI;

	printf("Enter an int and 2 characters: ");
	//scanf("%d%c%c", &randomIntI, &firstCharI, &secondCharI); normally spaces doesnt matter, but it does matter if you are
	// reading %c, as that will read the sapce, to fix this add a space
	scanf("%d %c %c", &randomIntI, &firstCharI, &secondCharI);


}
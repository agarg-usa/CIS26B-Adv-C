/*
 Task 1: Coding Style

 Rewrite addOdd() and countUpper() using good coding style.
 Updated the main() function if/as needed.

 Name: Aryan Garg
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int addOdd(int a, int b);
int countUpper(char password[]);

int main(  )
{
    char myPassword[] = "aBc12345@_bbAAA";
    int num1 = 10, num2 = 20, num3 = -5, num4 = 11;

    printf("%d %d sum = %d\n", num1, num2, addOdd(num1, num2));
    printf("%d %d sum = %d\n", num1, num3, addOdd(num1, num3));
    printf("%d %d sum = %d\n", num3, num4, addOdd(num3, num4));

    printf("%s has %d capital letters\n", myPassword, countUpper(myPassword));
    return 0;
}

/*
The following function works as expected but it could be improved.
Rewrite it to be shorter, more efficient, and easier to read.
 */
int addOdd(int a, int b)
{
    int sum = 0;
    // if (*a % 2 != 0 && *b % 2 != 0) // both *a and *b are odd
    //     sum = *a + *b;
    // if (*a % 2 != 0 && *b % 2 == 0) // only *a is odd
    //     sum = *a;
    // if (*a % 2 == 0 && *b % 2 != 0) // only *b is odd
    //     sum = *b;

	if(a % 2 == 1)
		sum += a;
	if(b % 2 == 1)
		sum += b;

    return sum;
}

/*
Rewrite the following code to eliminate the call for strlen() and isupper(),
and replace index k with a pointer.
*/
int countUpper(char password[])
{
    // int k, count;

    // k = count = 0;
    // while (k < strlen(password))
    // {
    //     if (isupper(password[k]))
    //         count++;
    //     k++;
    // }
    // return count;

	int count = 0;
	char* ptr = password;

	while(*ptr)
	{
		if(*ptr >= 'A' && *ptr <= 'Z')
			count++;
		ptr++;
	}

	return count;
}



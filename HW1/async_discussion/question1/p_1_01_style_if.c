/***************************************************
    Exercise 1.1
    Rewrite the following program using optimal C coding style.
    Pay attention to:
    - white spaces and indentation
    - short-cut boolean expressions in if or loop statements
    - use the conditional operator
    - code redundancy
    - proper use of the relational expression in a return statement
    - use of the comma operator in a loop
    - use of && and || to prevent if nesting

    Name: Aryan Garg
***************************************************/
#include <stdio.h>

int main (void)
{
    int a = 10, c = 0;

    if (a > 0)
    {
        c++;
    }
    else
    {
        a = -a;
    }

	printf("%d %d\n", a, c);

    return 0;
}

/** SAVE THE OUTPUT BELOW
 *
 * 10 1
 */

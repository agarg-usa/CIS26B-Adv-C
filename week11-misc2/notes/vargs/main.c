#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

double sumargs(int n, ...)
{
	va_list args;
	va_start(args, n);
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += va_arg(args, double); // NOTE: this is a macro, thats why we can pass in a double
	}
	va_end(args); // frees nodes
	return sum;
}

int main(void)
{
	double sum = sumargs(3, 1.0, 2.0, 3.0);
}
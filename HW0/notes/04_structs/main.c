#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
	double x;
	double y;
}Point;

Point calcMiddle(Point p1, Point p2);

int main(void)
{
	Point a = {4,5};
	Point b = {6,7};

	Point c = calcMiddle(a,b);
	printf("(%f, %f)\n", c.x, c.y);
}

Point calcMiddle(Point p1, Point p2)
{
	Point middle;
	middle.x = (p1.x + p2.x) / 2;
	middle.y = (p1.y + p2.y) / 2;
	return middle;
}

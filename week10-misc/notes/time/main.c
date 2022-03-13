#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
	time_t myTime;
	myTime = time(NULL);

	printf("%s", ctime(&myTime));
	char * chtime;
	struct tm* timeptr;
	timeptr = localtime(&myTime);
	chtime = asctime(timeptr);
	puts(chtime);

	// then you can also do other stuff like difftime
	sleep(1);
	printf("%f\n", difftime(myTime, time(NULL)));
	// you can conert this into a string using gmtime
	timeptr = gmtime(&myTime);
	// then convert this to whatever format you want using strftime
	char myString[100];
	strftime(myString, 100, "%a %b %d %H:%M:%S %Y", timeptr);
}
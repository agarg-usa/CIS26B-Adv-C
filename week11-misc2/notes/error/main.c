#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <assert.h>

jmp_buf env; // global var

void handler(int signum)
{
	if(signum == SIGSEGV)
	{
		printf("Segementation Fault Caught!\n");
		longjmp(env, 1);
	}
}

void endOfProg(void)
{
	printf("Exited out of main!\n");
}

int main(void)
{
	/*
		void (*signal(int  signal_code,
              void (*handler)(int signal_code)))(int)

	    signal is a function with two parameters:
		• signal_code, the code for a certain signal, and
		• a pointer to a function that will handle the signal if it’s
				raised later in the program
		that returns a pointer to a function with an int argument and
		void return type.
	*/

	// common signal codes:
	// SIGABRT (abort()), SIGINT (interrupt), SIGSEGV (segmentation fault), SIGFPE (floating point exception)
	// SIGETERM (terminate request)

	// common signal handlers:
	// SIG_DFL (default), SIG_IGN (ignore), your_func_name

	signal(SIGABRT, SIG_IGN); // ignores SIGABRT requests
	signal(SIGSEGV, handler); // calls handler() when SIGSEGV is raised

	int *p = NULL;
	// int a = *p; // seg fault


	if(setjmp(env) != 0) // macro that sets up a jmp location
	{
		printf("Jumped to this loc!\n");
	}
	else{
		raise(SIGSEGV); // calls handler()
	}

	// you can also time out programs using the alarm() function
	// setting up the alarm will raise a SIGALRM signal when the time expires

	signal(SIGALRM, SIG_IGN); // ignore SIGALRM requests
	// we can set it up to end prog for example instead
	alarm(5); // set up alarm to go off in 5 seconds
	// do stuff
	alarm(0); // cancel alarm

	// atextit is a funciton that will take in a function to call once main exits
	atexit(endOfProg); // calls endOfProg() when main exits

	//theres also assert(), which can be used for debugging
	assert(1);

	FILE* fp = fopen("test.txt", "r");
	if(fp == NULL)
	{
		perror("ERROR: "); // perror will decode the error code and print a message like "No such file or directory"
	}

	printf("End of prog!\n");

}
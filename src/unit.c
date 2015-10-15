/*
	author : ez
	date : 2015/5/19
	describe : stack declaration

*/

#include "_stack.h"
#include "ez.h"
#include <stddef.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


int* array;

int main (argc, argv)
	int argc;
	char* argv [];
{
	int i = 0;
	array = (int*) malloc (sizeof (int) * 100);

	srand (time (NULL));
	for (; i < 100; i ++) {
		array [i] = rand ();
		srand (array [i]);
	}

	_stack mystack = create_stack (120);

	printf ("empty? %s\n", 
		empty_stk (mystack) ? "true" : "false");

	if (!mystack || !array) {
		println ("error!\n");
		return 0;
	}

	for (i = 0; i < 100; i ++) {
		if (! push (mystack, array [i])) {
			printf ("push %d. %d error!\n", 
					i, array [i]);
		}
	}	

	printf ("full? %s\n", 
		full_stk (mystack) ? "true" : "false");


#ifdef __debug__
	show (mystack);
#endif // ~ __debug__

	printf ("top %d\n", top (mystack));
	for (i = 0; i < 100; i ++) {
		if (! pop (mystack)) {
			println ("pop element error!\n");
		}
	}

	dispose_stack (mystack);

	return 0;
}

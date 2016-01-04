/*
	author : ez
	date : 2015/5/19
	describe : stack declaration

*/

#include "ez_stack.h"
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

	pez_stack mystack = ez_stack_create (120);

	printf ("empty? %s\n", 
		ez_stack_empty (mystack) ? "true" : "false");

	if (!mystack || !array) {
		println ("error!\n");
		return 0;
	}

	for (i = 0; i < 100; i ++) {
		if (! ez_stack_push (mystack, array [i])) {
			printf ("push %d. %d error!\n", 
					i, array [i]);
		}
	}	

	printf ("full? %s\n", 
		ez_stack_full (mystack) ? "true" : "false");


#ifdef __debug__
	show (mystack);
#endif // ~ __debug__

	printf ("top %d\n", ez_stack_top (mystack));
	for (i = 0; i < 100; i ++) {
		if (! ez_stack_pop (mystack)) {
			println ("pop element error!\n");
		}
	}

	ez_stack_dispose (mystack);

	return 0;
}

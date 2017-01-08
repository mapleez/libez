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
pez_stack mystack;

static void _create_test ();
static void _full_empty_test ();
static void _push_test ();

static void _dump_stack ();


/* Create new stack entry. */
static void _create_test () {
	mystack = ez_stack_create (0);

	if (!mystack) {
		println ("error!\n");
		ez_stack_dispose (mystack);
		return;
	}

	_dump_stack (mystack);
	ez_stack_dispose (mystack);
	mystack = NULL;

	mystack = ez_stack_create (120);
	if (!mystack) {
		println ("error!\n");
		ez_stack_dispose (mystack);
		return;
	}

	_dump_stack (mystack);
	ez_stack_dispose (mystack);

	/* For other testing. */
	mystack = ez_stack_create (-9);
}

static void _full_empty_test () {
	println ("Starting full empty testing.");
	printf ("empty? %s\n", 
		ez_stack_empty (mystack) ? "true" : "false");

	printf ("full? %s\n", 
		ez_stack_full (mystack) ? "true" : "false");

	ez_stack_dispose (mystack);

	// ---------------------------------------- 
	println ("");
	mystack = ez_stack_create (0);

	printf ("empty? %s\n", 
		ez_stack_empty (mystack) ? "true" : "false");

	printf ("full? %s\n", 
		ez_stack_full (mystack) ? "true" : "false");

	ez_stack_dispose (mystack);

	// ---------------------------------------- 
	println ("");
	mystack = ez_stack_create (33); /* For last testing */

	printf ("empty? %s\n", 
		ez_stack_empty (mystack) ? "true" : "false");

	printf ("full? %s\n", 
		ez_stack_full (mystack) ? "true" : "false");

	// ez_stack_dispose (mystack);

	// ---------------------------------------- 
	pez_stack nullPtr = NULL;
	printf ("empty? %s\n", 
		ez_stack_empty (nullPtr) ? "true" : "false");

	printf ("full? %s\n", 
		ez_stack_full (nullPtr) ? "true" : "false");
	println ("Ending full empty testing.");
}

static void _push_test () {
	int i = 100;
	println ("Starting push test.");
	while (-- i) {
		void* e = ez_stack_push (mystack, (void*) i);
		if (e) {
			printf ("push %ld ok\n", (intptr_t) e);
		} else {
			printf ("push %ld error\n", (intptr_t) i);
		}
	}
	println ("Ending push test.");
}

int main (argc, argv)
	int argc;
	char* argv [];
{

	_create_test ();
	_full_empty_test ();

	_push_test ();
	_full_empty_test ();

#if 0
	int i = 0;
	array = (int*) malloc (sizeof (int) * 100);

	if (! array) {
		println ("Error malloc array.");
	}

	srand (time (NULL));
	for (; i < 100; i ++) {
		array [i] = rand ();
		srand (array [i]);
	}


	printf ("empty? %s\n", 
		ez_stack_empty (mystack) ? "true" : "false");

	printf ("full? %s\n", 
		ez_stack_full (mystack) ? "true" : "false");

	if (!mystack) {
		println ("error!\n");
		return 0;
	}

	for (i = 0; i < 100; i ++) {
		if (! ez_stack_push (mystack, (void*) array [i]))
			printf ("push %d. %d error!\n", 
					i, array [i]);
		else 
			printf ("push %d. %d ok!\n", 
					i, array [i]);
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
#endif

	return 0;
}

static void _dump_stack (pez_stack _s) {
	if (_s) {
		printf ("capa = %d\n"
					  "sp = %d\n"
						"array = %ld\n"
						"cls = %ld\n",
						_s -> capacity,
						_s -> sp,
						_s -> array,
						_s -> cls);
	}
}



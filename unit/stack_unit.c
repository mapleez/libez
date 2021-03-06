/*
	author : ez
	date : 2015/5/19
	describe : stack declaration

*/

#include "ez_stack.h"
#include "ez.h"
#include <stddef.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#	define BOOL2STR(__B)  ((__B) ? "true" : "false")

int* array;
pez_stack mystack;

static void _create_test ();
static void _full_empty_test ();
static void _push_test ();
static void _pop_test ();
static void _clear_test ();
static void _setcls_test ();

static void _dump_stack ();


/* Create new stack entry. */
static void _create_test () {
	println ("Start create and dispose testing.");
	println ("stack 0");
	pez_stack stack = ez_stack_create (0);

	if (! stack) {
		println ("error!\n");
		ez_stack_dispose (stack);
		return;
	}
	ez_stack_dispose (NULL);

	_dump_stack (stack);
	ez_stack_dispose (stack);
	stack = NULL;

	println ("stack 120");
	stack = ez_stack_create (120);
	if (! stack) {
		println ("error!\n");
		ez_stack_dispose (stack);
		return;
	}

	_dump_stack (stack);
	ez_stack_dispose (stack);

	println ("stack -9");
	stack = ez_stack_create (-9);
	_dump_stack (stack);
	ez_stack_dispose (stack);
	println ("End create and dispose testing.");
}

static void _full_empty_test () {
	int flag = 0;
	pez_stack stack = NULL;
	println ("Starting full empty testing.");
	println ("NULL stack.");

	flag = ez_stack_empty (stack);
	printf ("empty? %s\n", BOOL2STR (flag));

	flag = ez_stack_full (stack);
	printf ("full? %s\n", BOOL2STR (flag));

	// ---------------------------------------- 
	println ("Create 0 stack.");
	stack = ez_stack_create (0);

	flag = ez_stack_empty (stack);
	printf ("empty? %s\n", BOOL2STR (flag));

	flag = ez_stack_full (stack);
	printf ("full? %s\n", BOOL2STR (flag));

	ez_stack_dispose (stack);

	// ---------------------------------------- 
	println ("Create 33 stack.");
	stack = ez_stack_create (33); /* For last testing */

	flag = ez_stack_empty (stack);
	printf ("empty? %s\n", BOOL2STR (flag));

	flag = ez_stack_full (stack);
	printf ("full? %s\n", BOOL2STR (flag));

	ez_stack_dispose (stack);

	// ---------------------------------------- 
	println ("Ending full empty testing.");
}

static void _push_test () {
	int i = 100;
	pez_stack stack = NULL;
	println ("Starting push test.");
	println ("Push to NULL.");
	while (-- i) {
		void* e = ez_stack_push (stack, (void*) i);
		printf ("push %ld %s\n", i, BOOL2STR (e));
	}

	println ("--------------------");
	println ("Push to 32 stack.");
	stack = ez_stack_create (0x20);
	while (++ i < 100) {
		void* e = ez_stack_push (stack, (void*) i);
		printf ("push %d %s (return %ld)\n", i, 
			BOOL2STR (e), (intptr_t) e);
	}
	ez_stack_dispose (stack);
	println ("Ending push test.");
}


static void _pop_test () {
	println ("Starting pop test.");
	bool flag = ez_stack_pop (NULL); /* NULL */
	int i = 100, count = 0;
	while (-- i) {
 		/* 32 elements */
		if (ez_stack_pop (mystack)) {
			printf ("pop ok! full = %s; empty = %s\n",
				BOOL2STR (ez_stack_full (mystack)), 
				BOOL2STR (ez_stack_empty (mystack)));
		} else {
			printf ("pop error! full = %s; empty = %s\n",
				BOOL2STR (ez_stack_full (mystack)), 
				BOOL2STR (ez_stack_empty (mystack)));
		}
	}
	_dump_stack (mystack);

	while (++ i < 100) {
		count += ez_stack_push (mystack, (void*) i) ? 
			1 : 0;
	}
	println ("Pushed testing datas.");
	println ("Ending pop test.");
}

static void _clear_test () {
	println ("Starting clear test.");
	pez_stack stack = ez_stack_create (20);
	int i = 0;
	while (++ i <= 20) {
		void* e = ez_stack_push (stack, (void*) i);
		printf ("Push %ld\n", (intptr_t) e);
	}

	ez_stack_clear (stack);
	_dump_stack (stack);

	println ("____________________");
	ez_stack_clear (stack);
	_dump_stack (stack);

	ez_stack_clear (NULL);
	ez_stack_dispose (stack);
	println ("Ending clear test.");
}

static int _test_cls_func (const void* ptr) {
	(void) ptr;
	return 1;
}

static void _setcls_test () {
	pez_stack stack = ez_stack_create (0);
	int x = ez_stack_setcls (stack, _test_cls_func);
	printf ("%d\n", x);
}

/* Main entry. */
int main (argc, argv)
	int argc;
	char* argv [];
{
	// _create_test ();
	// _full_empty_test ();
	// _push_test ();
	// _pop_test ();
	// _clear_test ();
	// _setcls_test ();

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
						(intptr_t) _s -> array,
						(intptr_t) _s -> cls);
	}
}



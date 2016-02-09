#ifndef DBG
#	define DBG
#endif // ~ DBG

#include "ez_dlinklist.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

pez_dlist list;

void display_each (pdlist_elm _e) {
	if (! _e -> _value)
		println ("no value.");
	else
		printf ("%d\n", _e -> _value);
}

void signal_handler (int _signo) {
	printf ("start signal handler...\n");
	fprintf (stdout, 
			"I received a signal, numbered = %d\n", _signo);
	ez_dlist_dispose (&list);
	printf ("finished signal handler...\n");
	exit (0);
}

int main (int argc, char* argv []) {
	{
		list = ez_dlist_create ();
		pez_dlist dup = NULL;
		int i = 5;
		// display_dlist_head (list, display_each);
		// println ("--------------------");
		// display_dlist_tail (list, display_each);

		// test pushhead
		for (; i < 20; i ++) {
			pdlist_elm res = ez_dlist_pushhead (list, (void*)(long) i);
			printf ("push header %d\n", (long) (res -> _value));
		}
		// display_dlist_head (list, display_each);
		// println ("--------------------");
		// display_dlist_tail (list, display_each);

		println ("--------------------");

		// test pushtail
		for (; i >= 5; i --) {
			pdlist_elm res = ez_dlist_pushtail (list, (void*)(long) i);
			printf ("push tail %d\n", (long) (res -> _value));
		}
		display_dlist_head (list, display_each);
		println ("--------------------");
		// display_dlist_tail (list, display_each);

		println ("start search");
		pdlist_elm elm = ez_dlist_search (list, (void*)(long) 19);
		if (elm)
			printf ("prev value = %d, found value = %d, next value = %d\n",
				(elm -> _prev ? (elm -> _prev -> _value) : (void*)(long) -1),
				(elm -> _value),
				(elm -> _next ? (elm -> _next -> _value) : (void*)(long) -1));

		println ("--------------------");
		// duplication:
		dup = ez_dlist_duplicate (list);
		if (dup) {
			display_dlist_head (dup, display_each);
		} else {
			println ("duplicate error!");
		}

		if (list) ez_dlist_dispose (&list);
		if (dup) ez_dlist_dispose (&dup);
	}

	if (0)
	{
		if (signal (SIGINT, signal_handler) == SIG_ERR) {
			fprintf (stderr, "signal failed\n");
			return -1;
		}
		list = ez_dlist_create ();
		int i = 0;
		while (1) {
			for (i = 1; i < 0x7fffffff; i ++) {
				pdlist_elm res = ez_dlist_pushhead (list, (void*)(long) i);
				printf ("push header %d\n", (long) (res -> _value));
			}
		}
	}

	return 0;
}


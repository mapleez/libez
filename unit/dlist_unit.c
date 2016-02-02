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
	if (0)
	{
		list = ez_dlist_create (NULL, NULL);
		int i = 5;
		display_dlist_head (list, display_each);
		println ("--------------------");
		display_dlist_tail (list, display_each);

		// test pushhead
		for (; i < 20; i ++) {
			int res = (int) ez_dlist_pushhead (list, (void*) i);
			printf ("push header %d\n", res);
		}
		display_dlist_head (list, display_each);
		println ("--------------------");
		display_dlist_tail (list, display_each);

		println ("--------------------");

		// test pushtail
		for (; i >= 5; i --) {
			int res = (int) ez_dlist_pushtail (list, (void*) i);
			printf ("push tail %d\n", res);
		}
		display_dlist_head (list, display_each);
		println ("--------------------");
		display_dlist_tail (list, display_each);
		ez_dlist_dispose (&list);
	}

	{
		if (signal (SIGINT, signal_handler) == SIG_ERR) {
			fprintf (stderr, "signal failed\n");
			return -1;
		}
		list = ez_dlist_create (NULL, NULL);
		int i = 0;
		while (1) {
			for (i = 1; i < 0x7fffffff; i ++) {
				int res = (int) ez_dlist_pushhead (list, (void*) i);
				printf ("push header %d\n", res);
			}
		}
	}

	return 0;
}


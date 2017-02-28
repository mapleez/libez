#include <stdio.h>
#include "ez.h"
#include "ez_list.h"
#include "ez_stack.h"
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stddef.h>


int array [] = {
1,2,3,4,5,6,7,8,9, 10,
11,12,13, 14,15,16,17,18,19,20,21,22,23};

typedef void (*elm_prt) (void*);

static void __default_elm_print (void* p) {
	if (p)
		printf ("elm = %ld\n", p);
	else
		println ("elm = NULL");
}


static void _dump_list (elm_prt _print, pez_list _l) {
	pez_listnode e;
	if (! _print) _print = __default_elm_print;
	if (! _l) { println ("NULL List."); return; }
	printf ("-------------\n"
					"* size : %d\n"
					"* cmp : %ld\n"
					"* cls : %ld\n"
					"* dup : %ld\n"
					"-------------\n",
					_l -> size, _l -> cmp,
					_l -> cls, _l -> dup);
	e = _l -> elms;
	while (e) {
		_print (e -> val);
		e = e -> next;
	}
	println ("-------------");
}

// _list mylist;

void _create_test () {
	println ("------ Create testing ------");
	pez_list list = ez_list_create ();
	if (list) println ("Create good.");
	else println ("Create error.");
	_dump_list (NULL, list);
	ez_list_dispose (&list);
	println ("----------------------------");
}

void _push_test () {
	int i = 0;
	int j = 20;
	println ("------ Push   testing ------");
	pez_list list = ez_list_create ();
	if (! list) { println ("Create error"); return; }

	// while (j --) {

	  for (i = 0; i < SHRT_MAX/* sizeof (array) / sizeof (int)*/ ; i ++) {
			pez_listnode p = ez_list_pushtail (list, (void*) i);
			if (p) 
				printf ("Pushed element %d OK\n", p-> val);
			else 
				printf ("Push element %d ERR\n", i);
	  	// pez_listnode p = ez_list_pushhead (list, (void*) i); // (void*) array [i]);
	  	// if (p) printf ("Pushed element %d OK\n", p -> val);
	  	// else printf ("Pushed element %d ERR\n", i/* array [i]*/ );
	  }
	// }

	// _dump_list (NULL, list);

	ez_list_dispose (&list);
	println ("----------------------------");
}

void _push_test1 () {
	int i = 0;
	pez_list list = ez_list_create ();
	ez_list_setcls (list, ez_stack_dispose);

	
	for (; i < 100; i ++) {
		pez_stack s = ez_stack_create (20);
		pez_listnode node = NULL;
		if (! s) { println ("Creating stack error! "); continue; }
		node = ez_list_pushtail (list, s);
		if (node) {
			show (node -> val);
		} else {
			println ("Push list error!");
		}
	}

	ez_list_dispose (&list);
}

void _test_setfunc() {
	pez_list list = ez_list_create ();
	if (! list) { println ("Creating error."); return; }

	ez_list_setcls (list, NULL);
	// ez_list_setdup (list, NULL);
	// ez_list_setcmp (list, NULL);

	ez_list_dispose (list);
}


int main (argc, argv) 
	int argc;
	char* argv [];
{	
	// _create_test ();
	// _push_test ();
	// _test_setfunc();
	_push_test1 ();

#if 0
	if (0) {
		int i = 0;
		_position pos;
		mylist = ez_list_create ();
		if (! mylist) {
			println ("malloc error!");
			return 0;
		}
		pos = mylist;
		for (; i < 2; ++ i) {
			if (ez_list_insert (mylist, i, pos))
				printf ("Insert %d\n", i);
		}
		foreach_ez_list (pos, mylist, i)
			printf ("%d\n", i);
		println ("------------------");
		mylist = ez_list_reverse (mylist);
		foreach_ez_list (pos, mylist, i)
			printf ("%d\n", i);
	}

	if (0) {
		int i = 0, len = 23;
		int temp;
		_position ch;
		mylist = ez_list_create (); 
		// _element buf = (_element) malloc (sizeof (_element));
		if (NULL == mylist) {
			println ("malloc error!");
			return 0;
		}
		_position pos = mylist;

		// isempty ()
		if (ez_list_empty (mylist))
			println ("is empty!");
		// insert ()
		for (; i < len; i ++) {
			if (pos != NULL &&
					ez_list_insert (mylist, 
						array [i], pos)) {
				printf ("insert %d\n", array [i]);
			} else 
				printf ("insert %d error\n", array [i]);
			pos = (_position) (pos -> next);
		}

		if (ez_list_find (mylist, (int) 20)!= NULL) 
			printf ("find %d \n", 20);
		else 
			printf ("find %d error\n", 20); 


		if ((ch = ez_list_find_pre (mylist, (int) 12)) != NULL) 
			printf ("find_pre %d \n", ch -> val);
		else 
			printf ("find_pre %d error\n", ch -> val); 

		// testing reverse list
		mylist = ez_list_reverse (mylist);
		println ("finshed reverse.");
		foreach_ez_list (pos, mylist, temp)
			printf ("%d ", pos -> val);
		// for (pos = mylist; pos -> next; pos = pos -> next)
		println ("");

		ez_list_del_all (mylist);
	}
#endif

	return 0;
}

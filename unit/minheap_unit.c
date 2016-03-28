#include <stdio.h>
#include <stdlib.h>
#include "ez.h"
#include "ez_heap.h"
#include "ez_unit.h"

int arr [] = {
	1, 2, 5,
	3, 9, 7,
	21, 6, 0
};


static int _release_func (void* _dat) {
	printf ("release element %i\n", (long long int) _dat);
}

int main (int argc, char* argv []) {
	void** _arr;
	int i = 0;
	int* random_arr = random_int_range_array (10, 100, 20);
	int num = 20; // sizeof (random_arr) / sizeof (int);
	pez_minheap ptr = NULL;
	if (0) 
		ptr = ez_minheap_create (10);
	else { // testing ez_minheap_build ();
		_arr = (void**) malloc (sizeof (void*) * num);
		for (; i < num; i ++) {
			_arr [i] = (void*) random_arr [i];
			printf ("%d. %i\n", i, (long long int) _arr [i]);
		}
		ptr = ez_minheap_build (_arr, num, NULL);
		println ("--------------------");
		ez_minheap_disp (ptr);
	}
	println ("--------------------");

	for (i = 0; i < sizeof (arr) / sizeof (int); i ++)
		if (ez_minheap_insert (ptr, (void*) (arr [i])) == RTNVAL_FAIL)
			printf ("error in inserting %d.\n", arr [i]);
		else
			printf ("Successful in inserting %d.\n", arr [i]);

	ez_minheap_setrelease (ptr, _release_func);
	ez_minheap_disp (ptr);

	/* Delete minimum */
	if (ez_minheap_delmin (ptr)) {
		println ("Delete good.");
		ez_minheap_disp (ptr);
	}

	if (ez_minheap_delmin (ptr)) {
		println ("Delete good.");
		ez_minheap_disp (ptr);
	}

	if (ez_minheap_delmin (ptr)) {
		println ("Delete good.");
		ez_minheap_disp (ptr);
	}

	if (ez_minheap_delmin (ptr)) {
		println ("Delete good.");
		ez_minheap_disp (ptr);
	}
	println ("--------------------");

	ez_minheap_dispose (ptr);

	return 0;
}



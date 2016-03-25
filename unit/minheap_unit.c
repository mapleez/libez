#include <stdio.h>
#include <stdlib.h>
#include "ez.h"
#include "ez_minheap.h"

int arr [] = {
	1, 2, 3,
	5, 9, 7,
	21, 6, 0
};

static int _release_func (void* _dat) {
	printf ("release element %i\n", (long long int) _dat);
}

int main (int argc, char* argv []) {
	int i = 0;
	pez_minheap ptr = ez_minheap_create (10);
	for (i; i < sizeof (arr) / sizeof (int); i ++)
		if (ez_minheap_insert (ptr, (void*) (arr [i])) == RTNVAL_ERR)
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



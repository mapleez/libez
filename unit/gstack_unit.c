#include "ez_gstack.h"
#include "ez_unit.h"
#include <unistd.h>

#	define ARRAY_SIZE 20

int _release_elm (void* _data) {
	printf ("release elm %d\n", *(int*) _data);
}

int main (int argc, char* argv []) {
	int * array = random_int_array (ARRAY_SIZE);
	int i = 0;
	pez_gstack gs = ez_gstack_create (ARRAY_SIZE);

	{ // start testing.
		int* x;
		if (gs) {
			ez_gstack_setrelease (gs, _release_elm);
			for (; i < ARRAY_SIZE; ++ i) {
				void* res = ez_gstack_push (gs, array + i);
				if (res)
					printf ("push successful : %d\n", *(int*) res);
				else
					println ("return error.");
			}

			ez_gstack_pop (gs);
			ez_gstack_pop (gs);
			ez_gstack_pop (gs);
			if (x = ez_gstack_push (gs, array + 10)) {
				printf ("push array + 10 successful : %d\n", *x);
			}
			if (x = ez_gstack_push (gs, array + 13)) {
				printf ("push array + 13 successful : %d\n", *x);
			}
			// ez_gstack_push (gs, array + 13);

		} else {
			println ("create stack error.");
		}
	}

	ez_gstack_release (gs);
	return 0;
}


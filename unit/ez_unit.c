#include "ez_unit.h"
#include <stdlib.h>
#include <time.h>

int* random_int_array (int num) {
	int * array = (int*) 
		malloc (num * sizeof (int));

	int seed = time (NULL);
	while (num --) {
		srand (seed/*time (NULL)*/);
		seed = array [num] = rand ();
	}
	return array;
}


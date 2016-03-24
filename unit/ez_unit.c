#include "ez_unit.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static void __default_disp_each 
(const void*);

static void __default_disp_each 
(const void* _elm) {
	unsigned long long int value = 
		(unsigned long long int) _elm;
	printf ("%i ", value);
}

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

void display_array 
(const void* _arr, int _cnt, int _elm_size, 
 void (* _disp_each) (const void*)) {
	int i = 0;
	if (! _disp_each) 
		_disp_each = __default_disp_each;
	for (; i < _cnt; ++ i)
		_disp_each (_arr + i * _elm_size);
}


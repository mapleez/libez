#include "ez_unit.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// static int seed = 0;

static void __default_disp_each 
(const void*);

static int _random_int_range (int, int, int);

static void __default_disp_each 
(const void* _elm) {
	unsigned long long int value = 
		(unsigned long long int) _elm;
	printf ("%i ", value);
}

static int _random_int_range (int _min, int _max, int _seed) {
	int res = 0;
	srand (_seed);
	res = rand () % _max + _min;
	return res;
}

int* random_int_range_array 
(int _min, int _max, int _count) {
	int last = time (NULL);
	int i = 0;
	int* array = (int*) malloc (_count * sizeof (int));
	if (! array) return NULL;
	for (; i < _count; i ++)
		last = array [i] = 
			_random_int_range (_min, _max, last);
	return array;
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


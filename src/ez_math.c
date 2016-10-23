#include "ez_math.h"
#include "ez.h"

void ez_moronic_cowmpouter 
(uint32_t _num, uint32_t _base) {
	int cow [DEFAULT_COW_LEN] = {0, };
	int cow_len = 0;
	uint32_t num = _num;
	uint32_t temp = 0;

	while (temp = _num % _base, 
			_num /= _base, _num) {
		if (cow_len < DEFAULT_COW_LEN)
			cow [cow_len ++] = temp;
		else {
			println ("Out of memory.");
			return;
		}
	}

	cow [cow_len] = temp;
	// input
	printf ("%d = ", num);
	for (; cow_len >= 0; -- cow_len) {
		printf ("%d^%d + ", _base, cow [cow_len]);
	}
}

void* ez_array_max 
(const void** _arr, int _num, cmp_func _func) {
	
	_ez_array_max (void*, _arr, _num, _func);
	// void* max = NULL;
	// int i = 0;
	// if (! _arr || ! _func) return NULL;

	// max = (void*) _arr [i ++];
	// for (; i < _num; ++ i)
	// 	if (_func (max, _arr [i]) == SMALLER) 
	// 		max = _arr [i];

	// return max;
}


/*
 * Get the values of @1 times @3, each digit will stored
 * at one element in @1 array. and return the array being
 * computed.
 * @1 = array
 * @2 = the size of array
 * @3 = the multipler, only a single digit.
 * return the array being computed.
 */
int* ez_isingle_multipler (int* _big, size_t _len, int _n) {
	int i, j, k;
	if (! _big) return _big;
	for (; i < _n; ++ i)
		_multi (_big, _len, _n); // ERROR
	// TODO...

	return _big;
}

void _multi (int* _big, size_t _len, int _n) {
	for (int i = 0; i < _len; ++ i)
		_big [i] *= _n;
	for (int j = 0; j < _len - 1; ++ j) {
		_big [j + 1] += _big [j] / 10;
		_big [j] %= 10;
	}
}



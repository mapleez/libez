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
	for (; i < _n; ++ i) {
		_multi (_big, _len, _n); // ERROR
	}

	return _big;
}

/*
 * Multiple.
 */
int _multi (int* _big, size_t _len, int _n) {
	int len = _len, j = 0;
	int* tmp = _big; // point to the first;
	while (len -- > 0 && *_big)
		*_big ++ *= _n;

	for (; j < _len - len; ++ j) {
		tmp [j + 1] += tmp [j] / 10;
		tmp [j] %= 10;
	}
	return _len - len;

	// reverse array
	// while (tmp < _big) {
	// 	*tmp ^= *_big;
	// 	*_big ^= *tmp;
	// 	*tmp ^= *_big;
	// 	tmp ++;
	// 	_big --;
	// }
}

char* iarr2string (int* arr, size_t len) {
	int i = 0;
	char* ptr = (char*) malloc (len + 2);
	if (*ptr) return NULL;

	for (; i < len; ++ i)
		*(ptr + i) = '0' + *(arr + i);
	return ptr;
}

#if 1
int main (int argc, char* argv []) {
	int bignum [] = {2,3,4,5,6,8,1,0,0};
	char* res = NULL;
	int tmp = 0;
	tmp = _multi (bignum, sizeof (bignum) / sizeof (int), 8);
	printf ("%s\n", res = iarr2string (bignum, tmp));
	free (res);

	_multi (bignum, sizeof (bignum) / sizeof (int), 1);
	printf ("%s\n", res = iarr2string (bignum, tmp));
	free (res);

	_multi (bignum, sizeof (bignum) / sizeof (int), 3);
	printf ("%s\n", res = iarr2string (bignum, tmp));
	free (res);

	_multi (bignum, sizeof (bignum) / sizeof (int), 2);
	printf ("%s\n", res = iarr2string (bignum, 
		sizeof (bignum) / sizeof (int)));
	free (res);

	_multi (bignum, sizeof (bignum) / sizeof (int), 4);
	printf ("%s\n", res = iarr2string (bignum, 
		sizeof (bignum) / sizeof (int)));
	free (res);

	_multi (bignum, sizeof (bignum) / sizeof (int), 0);
	printf ("%s\n", res = iarr2string (bignum, 
		sizeof (bignum) / sizeof (int)));
	free (res);
	printf ("");
	return 0;
}
#endif




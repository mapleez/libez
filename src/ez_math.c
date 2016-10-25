#include "ez_math.h"
#include "ez.h"

static int* _single_multipler (int*, size_t, size_t, int);
static int* _multipler (int*, size_t, int*, size_t, int);

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
// int* ez_isingle_multipler (int* _big, size_t _len, int _n) {
// 	int i, j, k;
// 	if (! _big) return _big;
// 	for (; i < _n; ++ i) {
// 		_multi (_big, _len, _n); // ERROR
// 	}
// 
// 	return _big;
// }

/*
 * Single digit Multiply.
 * @1 a multiple digit number sequence with reverse order.
 *   Note single digit stored in one element. And the 
 *   length of array must longer than the array. The rest
 *   of elements not being used are set to 0.
 * @2 the max length of @1
 * @3 The sequence length, @2 - @3 must >= 1.
 * @4 Single digit that will multiply each element in array.
 *
 * Return the sequence. Note the sequence is still with reverse
 * order.
 */
static int* _single_multipler (int* _big, size_t _maxlen, 
 size_t _seclen, int _n) {
	int len = _seclen, j = 0;
  /* point to the first; */
	int* tmp = _big;

	while (len -- > 0 && _maxlen -- > 0)
		*_big ++ *= _n;

	for (; j <= _seclen; ++ j) {
		tmp [j + 1] += tmp [j] / 10;
		tmp [j] %= 10;
	}
	return _big;
}

// static int* _multipler 
//  (int* _a, size_t _alen, int* _b, size_t _ble) {
//   
// 	return _a;
// }

// TODO unit testing
// Ensure @1 has enough space for result of @1 + @2
static off_t _add 
 (int* _a, size_t _alen, int* _b, size_t _blen, off_t _start) {
 	off_t idxa = _start, idxb = 0;
	size_t rga = _alen + _start;
	size_t rgb = _blen + _start;
  if (!_a && !_b) return NULL;
	for (; idxa < rga || idxb < rgb; idxa ++, idxb ++) {
	  int* tmp = _a + idxa;
		*tmp += *(_b + idxb);
		*(tmp + 1) += *tmp / 10;
		*tmp %= 10;
	}
	return idxa > idxb ? idxa : idxb; // return the maximum.
}

char* iarr2string (int* arr, size_t len) {
	int i = 0;
	char* ptr = (char*) malloc (MEM_ALIGE(len + 2));
	if (*ptr) return NULL;

	// auto reverse array.
	for (; i < len; ++ i)
		*(ptr + len - i - 1) = '0' + *(arr + i);
	ptr [i] = '\0';
	return ptr;
}

#if 1
int main (int argc, char* argv []) {
	int bignum [] = {2,3,4,5,6,8,1,0,0}; // number 1865432
	int bignum1 [] = {3,9,2,3,0}; // number 3293
	off_t res = 0L;
	char* ptr = NULL;

	res = _add (bignum, 7l, bignum1, 4l, 1l);
	ptr = iarr2string (bignum, 7L);
	printf ("%s\n", ptr);

	// tmp = _multi (bignum, sizeof (bignum) / sizeof (int), 8);
	// free (res);

	// _multi (bignum, sizeof (bignum) / sizeof (int), 1);
	// printf ("%s\n", res = iarr2string (bignum, tmp));
	// free (res);

	// _multi (bignum, sizeof (bignum) / sizeof (int), 3);
	// printf ("%s\n", res = iarr2string (bignum, tmp));
	// free (res);

	// _multi (bignum, sizeof (bignum) / sizeof (int), 2);
	// printf ("%s\n", res = iarr2string (bignum, 
	// 	sizeof (bignum) / sizeof (int)));
	// free (res);

	// _multi (bignum, sizeof (bignum) / sizeof (int), 4);
	// printf ("%s\n", res = iarr2string (bignum, 
	// 	sizeof (bignum) / sizeof (int)));
	// free (res);

	// _multi (bignum, sizeof (bignum) / sizeof (int), 0);
	// printf ("%s\n", res = iarr2string (bignum, 
	// 	sizeof (bignum) / sizeof (int)));
	free (ptr);
	return 0;
}
#endif



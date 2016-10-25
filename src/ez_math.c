#include "ez_math.h"
#include "ez.h"

#include <string.h>

static int* _single_multipler (int*, size_t, size_t, int);
static int* _multipler (int*, size_t, int*, size_t, int);
static int* _string2iarr (char*, size_t);
static char* _iarr2string (int*, size_t);

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
  if (!_a && !_b) return -1;
	for (; idxa < rga || idxb < rgb; idxa ++, idxb ++) {
	  int* tmp = _a + idxa;
		*tmp += *(_b + idxb);
		*(tmp + 1) += *tmp / 10;
		*tmp %= 10;
	}
	return idxa > idxb ? idxa : idxb; // return the maximum.
}

char* _rev (char* _a, size_t _len) {
	char* ptr = _a;
	char* real = _a + _len - 1;

	while (ptr < real) {
		*ptr ^= *real;
		*real ^= *ptr;
		*ptr ^= *real;
		ptr ++;
		real --;
	}

	return _a;
}

char* ez_add (char* _a, size_t _alen, char* _b, size_t _blen) {
	int* a = _string2iarr (_a, _alen);
	int* b = _string2iarr (_b, _blen);
	char* res = NULL;
	off_t len = 0;

	if (!a || !b) goto ERR;
	len = _add (a, _alen, b, _blen, 0L);

	if (len > 0)
		res = _iarr2string (a, len);
	else
		goto ERR;

	if (! res) 
		goto ERR;
	if (a) free (a);
	if (b) free (b);
	return res;

ERR:
	if (a) free (a);
	if (b) free (b);

	return NULL;
}

#if 0
char* ez_add (char* _a, size_t _alen, char* _b, size_t _blen) {
	size_t bufflen;
	off_t idxshort, idxlong;
	static const int offset = 2;
	char* shorter = NULL;
	char* longer = NULL; // TODO
	char* buff = NULL;

	if (_alen > _blen) {
		bufflen = _alen;
		shorter = _b; // the shorter one.
		longer = _a;
		buff = (char*) malloc (MEM_ALEGE (bufflen + offset));
		if (! buff) return NULL;
	} else {
		bufflen = _blen;
		shorter = _a; // the shorter one.
		longer = _b;
		buff = (char*) malloc (MEM_ALEGE (bufflen + offset));
		if (! buff) return NULL;
	}

#	define charadd(a, b)  (((a) - '0') + ((b) - '0'))
#	define charsub(a, b)  (((a) - '0') - ((b) - '0'))

	memcpy (buff + offset, longer, bufflen);
	longer = buff + offset;
	idxlong = bufflen + offset - 1;
	for (; idxshort; -- idxshort, -- idxlong) {
		longer [idxlong] += (longer [idxlonger], shorter [idxshorter]);
		longer [idxlong] += shorter [idxshort] - '0';
		buff [idxa - 1] += (buff [idxa] - '0') / 10;
		buff [idxa] %= 10;
	}
}
#endif

static char* _iarr2string (int* arr, size_t len) {
	int i = 0;
	size_t xx = MEM_ALIGE (len + 2);
	char* ptr = (char*) malloc (MEM_ALIGE(len + 2));
	if (!ptr) return NULL;

	// auto reverse array.
	for (; i < len; ++ i)
		*(ptr + len - i - 1) = '0' + *(arr + i);
	ptr [i] = '\0';
	return ptr;
}

static int* _string2iarr (char* _arr, size_t _len) {
	int i = 0;
	size_t xx = MEM_ALIGE (_len + 2);
	int* ptr = (int*) malloc (xx * sizeof (int));
	int* tmp = ptr;
	if (!ptr) return NULL;

	for (; i < _len; ++ i)
		*(tmp + _len - i - 1) = *_arr ++ - '0';
	return ptr;
}

#if 1
int main (int argc, char* argv []) {
	
	// char* a = "2343728";
	// char* b = "3829";
	char* a = NULL, 
		*b = NULL;

	if (argc >= 3) {
		a = argv [1];
		b = argv [2];
	}

	char* res = ez_add (a, strlen (a), b, strlen (b));
	// printf ("%s + %s = %s\n", a, b, res);
	printf ("%s", res);

#if 0
	int bignum [] = {2,3,4,5,6,8,1,0,0}; // number 1865432
	int bignum1 [] = {3,9,2,3,0}; // number 3293
	off_t res = 0L;
	char* ptr = NULL;

	res = _add (bignum, 7l, bignum1, 4l, 1l);
	ptr = _iarr2string (bignum, 7L);
	printf ("%s\n", ptr);

	tmp = _multi (bignum, sizeof (bignum) / sizeof (int), 8);
	free (res);
#endif 

	// _multi (bignum, sizeof (bignum) / sizeof (int), 1);
	// printf ("%s\n", res = _iarr2string (bignum, tmp));
	// free (res);

	// _multi (bignum, sizeof (bignum) / sizeof (int), 3);
	// printf ("%s\n", res = _iarr2string (bignum, tmp));
	// free (res);

	// _multi (bignum, sizeof (bignum) / sizeof (int), 2);
	// printf ("%s\n", res = _iarr2string (bignum, 
	// 	sizeof (bignum) / sizeof (int)));
	// free (res);

	// _multi (bignum, sizeof (bignum) / sizeof (int), 4);
	// printf ("%s\n", res = _iarr2string (bignum, 
	// 	sizeof (bignum) / sizeof (int)));
	// free (res);

	// _multi (bignum, sizeof (bignum) / sizeof (int), 0);
	// printf ("%s\n", res = _iarr2string (bignum, 
	// 	sizeof (bignum) / sizeof (int)));
	// free (ptr);
	return 0;
}
#endif



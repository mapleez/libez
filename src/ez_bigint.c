#include "ez_bigint.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int ezbigi_iszero (pezbigi _num) {
	if (!_num) return 0;
	return _num -> len == 1 && 
		*_num -> cnum == '0';
}

int ezbigi_isequal (pezbigi, pezbigi);

pezbigi ezbigi_reset_by_char (pezbigi, const char*);
pezbigi ezbigi_reset_by_int (pezbigi, const int*);
pezbigi ezbigi_reset (pezbigi, pezbigi);

/*
 * Create a new bigint from char array, a string.
 * Note the string cannot include a signal symbol (-/+)
 * at this version.
 * @1 string.
 *
 * Return a pointer to ezbigi structure if successful.
 * Else return NULL;
 */
pezbigi ezbigi_create_by_char (const char* _cnum) {
	pezbigi bigi;
	size_t len;
	int i;
	if (! _cnum) 
		return NULL;

 	bigi = (pezbigi) malloc (sizeof (*bigi));
	if (! bigi) 
		return NULL;

	bigi -> len = len = strlen (_cnum);
	bigi -> capa = len + OVERFLOW_LEN;
	/* Including null terminal symbol. */
	bigi -> cnum = (char*) malloc (bigi -> capa + 1);
	bigi -> inum = (int*) malloc 
		(sizeof (int) * bigi -> capa);

	if (! bigi -> cnum || ! bigi -> inum)
		goto ERR;
	
	/* Copy char* num. */
	memcpy (bigi -> cnum, _cnum, len);

	/* Copy int* num. */
	for (i = 0; i < len; ++ i)
		*(bigi -> inum + i) = *(bigi -> cnum + i) - '0';
	*(bigi -> cnum + i) = '\0';
	return bigi;

ERR:
	if (bigi) {
		if (bigi -> cnum) free (bigi -> cnum);
		if (bigi -> inum) free (bigi -> inum);
		free (bigi);
	}
	return NULL;
}


/*
 * Create a new bigint from a int array.
 * Note all the element cannot smaller than 0 at this version.
 * That is, unsigned int.
 * @1 string.
 *
 * Return a pointer to ezbigi structure if successful.
 * Otherwise return NULL;
 */
pezbigi ezbigi_create_by_int (const int* _inum, int _len) {
	pezbigi bigi;
	int i;
	if (! _inum) 
		return NULL;

 	bigi = (pezbigi) malloc (sizeof (*bigi));
	if (! bigi) 
		return NULL;

	bigi -> len = _len;
	bigi -> capa = _len + OVERFLOW_LEN;
	/* Including null terminal symbol. */
	bigi -> cnum = (char*) malloc (bigi -> capa + 1);
	bigi -> inum = (int*) malloc 
		(sizeof (int) * bigi -> capa);

	if (! bigi -> cnum || ! bigi -> inum)
		goto ERR;
	
	/* Copy int* num. */
	memcpy (bigi -> inum, _inum, sizeof (int) * _len);

	/* Copy char* num. */
	for (i = 0; i < _len; ++ i)
		*(bigi -> cnum + i) = (char) ('0' + *(bigi -> inum + i));
	*(bigi -> cnum + i) = '\0';
	return bigi;

ERR:
	if (bigi) {
		if (bigi -> cnum) free (bigi -> cnum);
		if (bigi -> inum) free (bigi -> inum);
		free (bigi);
	}
	return NULL;
}

/*
 * Destroy a bigint. If @1 == NULL, then 
 * nothing will be done and return.
 */
void ezbigi_destroy (pezbigi _num) {
	if (! _num) return;
	if (! _num -> cnum) free (_num -> cnum);
	if (! _num -> inum) free (_num -> inum);

	_num -> len = _num -> capa = 0;
	_num -> cnum = NULL;
	_num -> inum = NULL;
	free (_num);
}

/*
 * Display a bigint to stdout. The format
 * is "NUMER(LENGTH/TOTAL_CAPACITY)".
 */
void ezbigi_disp (const pezbigi _num) {
	int i = 0;
	if (! _num) return;
	printf ("%s(%ld/%ld)", _num -> cnum, 
		_num -> len, _num -> capa);
}

pezbigi ezbigi_add (pezbigi, pezbigi);
pezbigi ezbigi_sub (pezbigi, pezbigi);
pezbigi ezbigi_multi (pezbigi, pezbigi);
pezbigi ezbigi_div (pezbigi, pezbigi);
pezbigi ezbigi_mod (pezbigi, pezbigi);

/* TODO Synchronise char*. And unit testing */
pezbigi ezbigi_incream (pezbigi _num) {
	int overflow [OVERFLOW_LEN] = {0, 0}; // length = 2
	int* ptr;

	if (! _num) return NULL;
 	ptr = _num -> inum + (_num -> len - 1);
	*ptr += 1;
	while (*ptr >= 10 && ptr > _num -> inum) {
		*(ptr - 1) += *ptr / 10;
		*ptr -- %= 10;
	}

	/* overflow */
	if (ptr == _num -> inum) {
		*overflow += *ptr / 10;
		*ptr %= 10;
		/* Remaining enough space. */
		if (_num -> capa - _num -> len >= 1) {
			memmove (ptr - 1, ptr, _num -> len);
			*_num -> inum = *overflow;
			_num -> len ++;
		} else {
			/* Remaining no space. */
			int* tmp = (int*) realloc (ptr, 
				_num -> capa * MEM_REALLOC_RATE);
			if (! tmp) return NULL; // TODO, should recover former stat
			memmove (tmp + 1, ptr, _num -> len);
			*tmp = *overflow;
			_num -> inum = tmp;
			_num -> len ++;
			_num -> capa *= MEM_REALLOC_RATE;
		}
	}

	return _num;
}

pezbigi ezbigi_decream (pezbigi);

pezbigi ezbigi_zero (pezbigi);


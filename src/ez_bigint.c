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
	bigi -> cnum = (char*) malloc (bigi -> capa);
	bigi -> inum = (int*) malloc 
		(sizeof (int) * bigi -> capa);

	if (! bigi -> cnum || ! bigi -> inum)
		goto ERR;
	
	/* Copy char* num. */
	memcpy (bigi -> cnum, _cnum, len);

	/* Copy int* num. */
	for (i = 0; i < len; ++ i)
		*(bigi -> inum + i) = *(bigi -> cnum + i) - '0';
	return bigi;

ERR:
	if (bigi) {
		if (bigi -> cnum) free (bigi -> cnum);
		if (bigi -> inum) free (bigi -> inum);
		free (bigi);
	}
	return NULL;
}

pezbigi ezbigi_create_by_int (const int*);

/*
 * Destroy a bigint. If @1 == NULL, then 
 * nothing will be done and return.
 */
void ezbigi_destroy (pezbigi _num) {
	if (! _num) return;
	if (! _num -> cnum) free (_num -> cnum);
	if (! _num -> inum) free (_num -> inum);

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
pezbigi ezbigi_incream (pezbigi);
pezbigi ezbigi_decream (pezbigi);

pezbigi ezbigi_zero (pezbigi);


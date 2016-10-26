#ifndef _EZ_BIGINT_H_
#	define _EZ_BIGINT_H_

// #include "ez.h"
#include <stdlib.h>

#	define OVERFLOW_LEN 2

typedef struct _ezbigi {
	size_t len;
	size_t capa;
	char* cnum;
	int* inum;
} ezbigi, * pezbigi;

extern int ezbigi_iszero (pezbigi);
extern int ezbigi_isequal (pezbigi, pezbigi);

extern pezbigi ezbigi_reset_by_char (pezbigi, const char*);
extern pezbigi ezbigi_reset_by_int (pezbigi, const int*);
extern pezbigi ezbigi_reset (pezbigi, pezbigi);

/*
 * Create a new bigint from char array, a string.
 * Note the string cannot include a signal symbol (-/+)
 * at this version.
 * @1 string.
 *
 * Return a pointer to ezbigi structure if successful.
 * Otherwise return NULL;
 */
extern pezbigi ezbigi_create_by_char (const char*);

/*
 * Create a new bigint from a int array.
 * Note all the element cannot smaller than 0 at this version.
 * That is, unsigned int.
 * @1 The array.
 * @2 The length of @1
 *
 * Return a pointer to ezbigi structure if successful.
 * Otherwise return NULL;
 */
extern pezbigi ezbigi_create_by_int (const int*, int);

/*
 * Destroy a bigint. If @1 == NULL, then 
 * nothing will be done and return.
 */
extern void ezbigi_destroy (pezbigi);

/*
 * Display a bigint to stdout. The format
 * is "NUMER(LENGTH/TOTAL_CAPACITY)".
 */
extern void ezbigi_disp (const pezbigi);

extern pezbigi ezbigi_add (pezbigi, pezbigi);
extern pezbigi ezbigi_sub (pezbigi, pezbigi);
extern pezbigi ezbigi_multi (pezbigi, pezbigi);
extern pezbigi ezbigi_div (pezbigi, pezbigi);
extern pezbigi ezbigi_mod (pezbigi, pezbigi);
extern pezbigi ezbigi_incream (pezbigi);
extern pezbigi ezbigi_decream (pezbigi);

extern pezbigi ezbigi_zero (pezbigi);

#endif // ~ _EZ_BIGINT_H_



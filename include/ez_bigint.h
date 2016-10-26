#ifndef _EZ_BIGINT_H_
#	define _EZ_BIGINT_H_

// #include "ez.h"

typedef struct _ezbigi {
	int len;
	int capa;
	char* cnum;
	int* inum;
} ezbigi, * pezbigi

extern bool ezbigi_iszero (pezbigi);
extern bool ezbigi_isequal (pezbigi, pezbigi);

extern pezbigi ezbigi_reset_by_char (pezbigi, const char*);
extern pezbigi ezbigi_reset_by_int (pezbigi, const int*);
extern pezbigi ezbigi_reset (pezbigi, pezbigi);

extern pezbigi ezbigi_create_by_char (const char*);
extern pezbigi ezbigi_create_by_int (const int*);
extern void ezbigi_destroy (pezbigi);

extern pezbigi ezbigi_add (pezbigi, pezbigi);
extern pezbigi ezbigi_sub (pezbigi, pezbigi);
extern pezbigi ezbigi_multi (pezbigi, pezbigi);
extern pezbigi ezbigi_div (pezbigi, pezbigi);
extern pezbigi ezbigi_mod (pezbigi, pezbigi);
extern pezbigi ezbigi_incream (pezbigi);
extern pezbigi ezbigi_decream (pezbigi);

extern pezbigi ezbigi_zero (pezbigi);

#endif // ~ _EZ_BIGINT_H_



#include "ez_bigint.h"

bool ezbigi_iszero (pezbigi num) {
	if (!num) return false;
	return num -> len == 1 && 
		*num -> cnum == '0';
}

bool ezbigi_isequal (pezbigi, pezbigi);

pezbigi ezbigi_reset_by_char (pezbigi, const char*);
pezbigi ezbigi_reset_by_int (pezbigi, const int*);
pezbigi ezbigi_reset (pezbigi, pezbigi);

pezbigi ezbigi_create_by_char (const char*);
pezbigi ezbigi_create_by_int (const int*);
void ezbigi_destroy (pezbigi);

pezbigi ezbigi_add (pezbigi, pezbigi);
pezbigi ezbigi_sub (pezbigi, pezbigi);
pezbigi ezbigi_multi (pezbigi, pezbigi);
pezbigi ezbigi_div (pezbigi, pezbigi);
pezbigi ezbigi_mod (pezbigi, pezbigi);
pezbigi ezbigi_incream (pezbigi);
pezbigi ezbigi_decream (pezbigi);

pezbigi ezbigi_zero (pezbigi);


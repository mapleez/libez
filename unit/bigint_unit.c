#include "ez_bigint.h"

int main (int argc, char* argv []) {

	if (argc < 2) return 0;
	pezbigi bi = ezbigi_create_by_char (argv [1]);
	ezbigi_disp (bi);
	ezbigi_destroy (bi);
	return 0;
}


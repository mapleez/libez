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



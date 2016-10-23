#ifndef _EZ_MATH_H_
#	define _EZ_MATH_H_

#include <stdint.h>
#include "ez.h"

#	define DEFAULT_COW_LEN  32

#	define _ez_array_max(___TYPE, ___ARRAY, ___N, ___FUNC)  \
	{ \
		___TYPE max = (___TYPE) NULL; \
		int i = 0; \
		if (! ___ARRAY || ! ___FUNC) return (___TYPE) NULL; \
		max = (___TYPE) ___ARRAY [i ++]; \
		for (; i < ___N; ++ i) \
			if (___FUNC (max, ___ARRAY [i]) == SMALLER)  \
				max = ___ARRAY [i]; \
		return (___TYPE) max; \
	}

/*
 * Convert decimal to other based number.
 * @1 = Decimal, with 32bits length.
 * @2 = Based number.
 */
extern void ez_moronic_cowmpouter (uint32_t, uint32_t);

/*
 * Get the maximum element from array.
 * @1 = array
 * @2 = the number of element in array.
 * @3 = comparation function between two elements.
 * return max element.
 */
extern void* ez_array_max (const void**, int, cmp_func);

/*
 * Get the values of @1 times @3, each digit will stored
 * at one element in @1 array. and return the array being
 * computed.
 * @1 = array
 * @2 = the size of array
 * @3 = the multipler, only a single digit.
 * return the array being computed.
 */
extern int* ez_isingle_multipler (int*, size_t, int);


#endif // ~ _EZ_MATH_H_

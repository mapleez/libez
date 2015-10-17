#include "ez_search.h"

/*
   Binary Search
   if found, return index in @1,
   else return -1.
*/
int
ez_binary_search (
	const void* arr,
	int num,
	size_t elm_size,
	cmp_func fxn, // Comparation function
	const void* key)
{
	int mid, high = num - 1, low = 0;
	while (low <= high) {
		mid = (high + low) / 2;
		if (0 == fxn (arr + mid * elm_size, key))
			return mid; // found it!
		else if (-1 == 
				fxn (arr + mid * elm_size, key))
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1; // cannot found
}

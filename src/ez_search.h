#ifndef _EZ_SEARCH_H_
#	define _EZ_SEARCH_H_

#include "ez.h"

/*
   Binary Search
   if found, return index in @1,
   else return -1.
*/
extern
int ez_binary_search (const void*, int, 
		size_t, cmp_func, const void* key);

#endif // ~ _EZ_SEARCH_H_

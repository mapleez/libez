#ifndef _EZ_SORT_H_
#	define _EZ_SORT_H_

#include <stdbool.h>

#	define BIGGER	(-1)
#	define EQUAL  	(0)
#	define SMALLER  (1)

#	define ORDER_DESC     (true)
#	define ORDER_ASC	  (false)

typedef int (*cmp_func)(const void*, const void*);

extern
void ez_swap (void*, void*);

// #	define ez_swap(___A, ___B)   \
// 	do { \
// 		(___A) ^= (___B); \
// 		(___B) ^= (___A); \
// 		(___A) ^= (___B); \
// 	} while (0)


/*
   Straight Insertion sort
*/
extern
void ez_insert_sort (void*, int, size_t, cmp_func);


#endif // ~ _EZ_SORT_H_

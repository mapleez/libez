#ifndef _EZ_SORT_H_
#	define _EZ_SORT_H_

#include <stdbool.h>

#	define BIGGER	(-1)
#	define EQUAL  	(0)
#	define SMALLER  (1)

#	define ORDER_DESC     (true)
#	define ORDER_ASC	  (false)

typedef int (*cmp_func)(const void*, const void*);

#	define BASIC_SWAP(___A, ___B) \
		do {  \
			___A ^= ___B;  \
			___B ^= ___A;  \
			___A ^= ___B;  \
		} while (0)

/*
   Memory Swap
*/
extern
size_t ez_mem_swap (void*, void*, size_t);

/*
   Selection Sort
*/
extern
void ez_select_sort (void*, int, size_t, cmp_func, bool);

/*
   Straight Insertion sort
*/
extern
void ez_insert_sort (void*, int, size_t, cmp_func, bool);

/*
   Bubble Sort
*/
extern
void ez_bubble_sort (void*, int, size_t, cmp_func, bool);

#endif // ~ _EZ_SORT_H_

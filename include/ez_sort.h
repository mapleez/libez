#ifndef _EZ_SORT_H_
#	define _EZ_SORT_H_

#include <stdbool.h>
#include "ez.h"


/*
   Memory Swap
*/
extern
size_t ez_mem_swap (void*, void*, size_t);

/*
 * Simple Swap
*/
#	define ez_simple_swap(___type, ___a, ___b)  \
	do {    \
		*(___type*) ___a ^= *(___type*) ___b;	\
		*(___type*) ___b ^= *(___type*) ___a;	\
		*(___type*) ___a ^= *(___type*) ___b;	\
	} while (0);


/*
   Pointer Swap
*/
extern
void ez_ptr_swap (void* *, void* *);

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

#if 0
extern
void ez_insert_sort_i (int*, int, cmp_func);
#endif

/*
   Bubble Sort
*/
extern
void ez_bubble_sort (void*, int, size_t, cmp_func, bool);

#endif // ~ _EZ_SORT_H_

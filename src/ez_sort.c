/*
 * Author : ez
 * Create Date : 2015/10/14
 * Describe : sort algorithm.
*/

#include "ez.h"
#include "ez_sort.h"
#include <stdint.h>
#include <stddef.h>

void ez_swap (void* a, void* b) {
	void* tmp = a;
	a = b;
	b = tmp;
	// ((intptr_t) a) ^= (intptr_t) b;
	// ((intptr_t) b) ^= (intptr_t) a;
	// ((intptr_t) a) ^= (intptr_t) b;
}

void
ez_insert_sort (
		void* arr, 
		int num, 
		size_t elm_size,
		cmp_func cmpfxn,
		bool asc)
{

	int index, ptr;
	void* tmp = NULL;
	int order_flag = asc ? 
		SMALLER: // from bigger to smaller
		BIGGER; // from smaller to bigger

	if (!arr || !cmpfxn)
		return;
	// important
	tmp = malloc (elm_size);
	for (index = 1; index < num; ++ index) {
		ptr = index - 1;
		// important
		memcpy (tmp, (arr + index * elm_size), elm_size);

		while (ptr >= 0 && 
			  (func (arr + ptr * elm_size, tmp) == order_flag))
		{
			memcpy (arr + (ptr + 1) * elm_size, 
					arr + ptr * elm_size,
					elm_size);
			ptr --;
		}
		memcpy (arr + (ptr + 1) * elm_size, tmp, elm_size);
	}
}


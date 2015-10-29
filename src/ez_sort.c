/*
 * Author : ez
 * Create Date : 2015/10/14
 * Describe : sort algorithm.
*/

#include "ez.h"
#include "ez_sort.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/*
   swap memory block
*/
size_t ez_mem_swap (void* a, void* b, size_t size) {
	void* tmp = NULL;
	if (!a || !b || !size) 
		return 0;
	tmp = malloc (size);
	memcpy (tmp, a, size);
	memcpy (a, b, size);
	memcpy (b, tmp, size);
	free (tmp);
	tmp = NULL;
	return size;
}

/*
   Selection Sort
*/
void 
ez_select_sort (
		void* arr, 
		int num, 
		size_t elm_size, 
		cmp_func fxn,
		bool asc)  // from big to small
{
	int index, step = 0, min;
	int order_flag = asc ? 
		SMALLER :  // from big to small
		BIGGER;		// from small to big

	if (! arr || num <= 0 || ! fxn)
		return;

	for (index = 0; index < num - 1; ++ index) {
		min = index;
		for (step = index + 1; step < num; ++ step)
			if (order_flag == 
					fxn (arr + step * elm_size, 
						arr + min * elm_size)) 
				min = step;
		
		if (min != index) {
			ez_mem_swap (arr + index * elm_size,
					arr + min * elm_size,
					elm_size);
			/*
			memcpy (temp, 
					arr + index * elm_size, 
					elm_size);

			memcpy (arr + index * elm_size, 
					arr + min * elm_size, 
					elm_size);

			memcpy (arr + min * elm_size, 
					temp, 
					elm_size);
			*/
		}
	}

	// free (temp);
	// temp = NULL;
}


/*
   Insertion Sort
*/
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
			  (cmpfxn (arr + ptr * elm_size, tmp) == order_flag))
		{
			memcpy (arr + (ptr + 1) * elm_size, 
					arr + ptr * elm_size,
					elm_size);
			ptr --;
		}
		memcpy (arr + (ptr + 1) * elm_size, tmp, elm_size);
	}

	free (tmp);
	tmp = NULL;
}


/*
   Bubble Sort
*/
void 
bubble_sort (
		void* arr, 
		int num, 
		size_t elm_size, 
		cmp_func func,
		bool asc) 
{
	int index = num - 1, step;
	int order = asc ?
		SMALLER : // from small to big 
		BIGGER; // from big to small

	if (! arr || ! num || ! elm_size)
		return;
	while (index > 0) {
		for (step = 0; step < index; ++ step) {
			if (order == 
					func (arr + step * elm_size, 
						arr + (step + 1) * elm_size)) {
				ez_mem_swap (arr + step * elm_size,
							 arr + (step + 1) * elm_size,
							 elm_size);
				/*
				memcpy (temp, arr + step * elm_size, elm_size);
				memcpy (arr + step * elm_size, arr + (step + 1) * elm_size, elm_size);
				memcpy (arr + (step + 1) * elm_size, temp, elm_size);
				*/
			}
		}
		-- index;
	}

}



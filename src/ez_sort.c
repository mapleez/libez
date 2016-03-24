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

static int __default_cmp_func (const void*, const void*);

static int __default_cmp_func (const void* _a, const void* _b) {
	return _a > _b ? BIGGER : 
		_a == _b ? EQUAL : SMALLER;
}

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


// void ez_simple_swap (void* _a, void* _b) {
// 	*(int*) _a ^= *(int*) _b;
// 	*(int*) _b ^= *(int*) _a;
// 	*(int*) _a ^= *(int*) _b;
// }

/*
   Pointer Swap
*/
void ez_ptr_swap (void** _a, void** _b) {
	int* tmp = (int*) *_a;
	*_a = *_b;
	*_b = (void*) tmp;
	// (intptr_t _a, intptr_t _b) {

	// ((intptr_t) *_a) ^= ((intptr_t) *_b);
	// ((intptr_t) *_b) ^= ((intptr_t) *_a);
	// ((intptr_t) *_a) ^= ((intptr_t) *_b);

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
		BIGGER: // from bigger to smaller
		SMALLER; // from smaller to bigger

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

#if 0 
/* only for debug */
void ez_insert_sort_i (int* arr, 
		int num, cmp_func cmpfxn) {
	
	int index, ptr;
	int tmp = 0;
	// TODO ... error when ASC
	// int order_flag = asc ? 
	//	SMALLER: // from bigger to smaller
	//	BIGGER; // from smaller to bigger

	if (!arr || !cmpfxn)
		return;
	for (index = 1; index < num; ++ index) {
		ptr = index - 1;
		// important
		// memcpy (tmp, (arr + index * elm_size), elm_size);
		tmp = arr [index];

		while (ptr >= 0 && 
			  (cmpfxn (arr + ptr, &tmp) == SMALLER))
		{
			// memcpy (arr + (ptr + 1) * elm_size, 
			// 		arr + ptr * elm_size,
			// 		elm_size);
			arr [ptr + 1] = arr [ptr];
			ptr --;
		}
		// memcpy (arr + (ptr + 1) * elm_size, tmp, elm_size);
		arr [ptr + 1] = tmp;
	}

	// free (tmp);
	// tmp = NULL;
}
#endif // DEBUG

/*
   Bubble Sort
*/
void 
ez_bubble_sort (
		void* arr, 
		int num, 
		size_t elm_size, 
		cmp_func func,
		bool asc) 
{
	int index = num - 1, step;
	int order = asc ?
		BIGGER: // from small to big 
		SMALLER; // from big to small

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
			}
		}
		-- index;
	}

}


// TODO this algorithm is incorrect.
void ez_shell_sort 
(void* _arr, int num, size_t elm_size, 
 cmp_func func, bool asc) {
	int i, j, inc;
	int /* void* */ temp;
	if (! func) func = __default_cmp_func;
	for (inc = num / 2; inc > 0; inc /= 2)
		for (i = inc; i < num; ++ i) {
			temp = i; // we only record the index.
			for (j = i; j >= inc; j -= inc)
				if (func (_arr + temp * elm_size, 
							_arr + (j - inc) * elm_size) == SMALLER)
					memcpy (_arr + j * elm_size, 
							_arr + (j - inc) * elm_size, elm_size);
				else break;
			memcpy (_arr + j * elm_size, 
					_arr + temp * elm_size, elm_size);
		}
}


/*
 * This function is just for algorithm testing.
*/
static void 
__shell_sort (int* _arr, int _cnt) {
	int i, j, tmp, inc;
	for (inc = _cnt / 2; inc > 0; inc /= 2)
		for (i = inc; i < _cnt; i ++) {
			tmp = _arr [i];
			for (j = i; j >= inc; j -= inc)
				if (tmp < _arr [j - inc]) 
					_arr [j] = _arr [j - inc];
				else
					break;
			_arr [j] = tmp;
		}
}


#if 0
int main (int argc, char* argv []) {
	
	char x = '\x30';
	char y = '\x39';
	// int* a = &argc;
	// int x = 100;
	// int y = 20;
	// int* b = &x;
	// ez_ptr_swap (&a, &b);
	ez_simple_swap (char, &x, &y);

	printf ("");
	return 0;

}
#endif


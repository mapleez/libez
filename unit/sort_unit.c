#include "ez_sort.h"

int int_cmp (const void*, const void*);

#	define NUM 12

int array [] = {
	9,32,12,
	87,423,98,
	2,321,8,
	87,989, 23
};


int int_cmp (const void* a,
		const void* b) {
	int res = *(int*)a > *(int*)b ?
		-1 : *(int*)a - *(int*)b ?
		0 : 1;
	return res;
}

int main (int argc, char* argv []) {

	int i = 0;
	// TODO, error when ASC
	// ez_insert_sort (array, NUM, sizeof (int), int_cmp, false);
	// ez_select_sort (array, NUM, sizeof (int), int_cmp, true);
	ez_bubble_sort (array, NUM, sizeof (int), int_cmp, true);
	for (; i < NUM; ++ i)
		printf ("array [%d] = %d\n",
				i, array [i]);
	return 0;
}

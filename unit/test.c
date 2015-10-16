#include <stdio.h>
// #include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef int (*cmp_func) (const void*, const void*);

int* random_array (int num) {
	int seed = time (NULL);
	int i = 0;
	int * array = (int*) 
		malloc (num * sizeof (int));
	if (! array) 
		return NULL;
	for (; i < num; i ++) {
		srand (seed/*time (NULL)*/);
		seed = array [i] = rand ();
	}
	return array;
}

int a [] = {
	3, 8, 9,
	4, 1, 6,
	5
	/*
	9, 3, 2,
	92, 97, 12,
	923, 34, 23,
	278, 1, 0
	*/
};

#	define NUM 7
// insert sort
void insert_sort (int* arr, int num) {
	/*
	int i, j;
	int tmp;
	for (i = 1; i < num; i ++) {
		tmp = arr [i];
		j = i - 1;
		while (j >= 0 && tmp > arr [j]) {
			arr [j + 1] = arr [j --];
		}
		arr [j + 1] = tmp;
	}
	*/
	int index/*, ptr, temp*/;
	for (index = 1; index < num; ++ index) {
		int ptr = index - 1;
		int temp = arr [index];

		while (ptr >= 0 && arr [ptr] > temp) {
			arr [ptr + 1] = arr [ptr --];
			// ptr --;
		}

		arr [ptr + 1] = temp;
	}
}
// #include <stdint.h>
// #include <stddef.h>
// insert sort
void insert_sort_t (void* arr, int num, size_t elm_size, cmp_func func) {
	int index, ptr;
	void* tmp = malloc (elm_size);
	// int length = num * elm_size;
	for (index = 1; index < num; ++ index) {
		ptr = index - 1;
		memcpy (tmp, (arr + index * elm_size), elm_size);

		while (ptr >= 0 && 
			  (func (arr + ptr * elm_size, tmp) == 1))
		{
			memcpy (arr + (ptr + 1) * elm_size, 
					arr + ptr * elm_size,
					elm_size);
			ptr --;
		}
		memcpy (arr + (ptr + 1) * elm_size, tmp, elm_size);
	}
}

// select sort test
void select_sort (int * arr, int num) {
	int index, step = 0, min;
	for (index = 0; index < num - 1; ++ index) {
		min = index;
		for (step = index + 1; step < num; ++ step)
			if (arr [step] < arr [min]) min = step;

		if (min != index) {
			arr [index] ^= arr [min];
			arr [min] ^= arr [index];
			arr [index] ^= arr [min];
			/*
			temp = arr [index];
			arr [index] = arr [min];
			arr [min] = temp;
			*/
		}
	}
}


void select_sort_t (void* arr, int num, size_t elm_size, cmp_func fxn) {
	int index, step = 0, min;
	void* temp = malloc (elm_size);
	for (index = 0; index < num - 1; ++ index) {
		min = index;
		for (step = index + 1; step < num; ++ step)
			if (1 == fxn (arr + step * elm_size, arr + min * elm_size)) min = step;
		
		if (min != index) {
			memcpy (temp, arr + index * elm_size, elm_size);
			memcpy (arr + index * elm_size, arr + min * elm_size, elm_size);
			memcpy (arr + min * elm_size, temp, elm_size);
		}
	}

	free (temp);
}

// bubble sort
void bubble_sort (int * arr, int num) {
	int index = num - 1, step;
	while (index > 0) {
		for (step = 0; step < index; ++ step) {
			if (arr [step] > arr [step + 1]) {
				// int temp = arr [step];
				// arr [step] = arr [step + 1];
				// arr [step + 1] = temp;
				arr [step] ^= arr [step + 1];
				arr [step + 1] ^= arr [step];
				arr [step] ^= arr [step + 1];

			}
		}
		-- index;
	}
}

void 
bubble_sort_t (void* arr, int num, size_t elm_size, cmp_func func) {
	int index = num - 1, step;
	void* temp = malloc (elm_size);
	while (index > 0) {
		for (step = 0; step < index; ++ step) {
			if (-1 == func (arr + step * elm_size, 
						arr + (step + 1) * elm_size)) {
				memcpy (temp, arr + step * elm_size, elm_size);
				memcpy (arr + step * elm_size, arr + (step + 1) * elm_size, elm_size);
				memcpy (arr + (step + 1) * elm_size, temp, elm_size);
			}
		}
		-- index;
	}

	free (temp);
	temp = NULL;
}

int cmp_int_func (const void* a, const void* b) {
	if (*(int*)a > *(int*)b)
		return -1;
	else 
		return 1;
}

int
main (int argc, char* argv []) {
	int i = 0;
	int * array = random_array (5);
	for (; i < 5; ++ i) {
		printf ("arr [%d] = %d\n", i, array [i]);
	}
	printf ("\n--------------------\n");

	// insert_sort ((void*) a, NUM);
	// insert_sort_t ((void*) a, NUM, sizeof (int), cmp_int_func);
	// selection_sort (array, 20);
	
	// if (array)
	bubble_sort_t (array, 5, sizeof (int), cmp_int_func);
	// bubble_sort (array, 5);
//	else 
//		printf ("%s\n", "error...");
// 	sleep (2);
	for (i = 0; i < 5; ++ i) {
		printf ("arr [%d] = %d\n", i, array [i]);
	}
	// printf ("\n--------------------\n");
	return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef int (*cmp_func) (const void*, const void*);

int* random_array (int num) {
	int * array = (int*) 
		malloc (num * sizeof (int));
	int seed = time (NULL);
	int i = 0;
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

int cmp_int_func (const void* a, const void* b) {
	if (*(int*)a > *(int*)b)
		return -1;
	else 
		return 1;
}

int
main (int argc, char* argv []) {
	int i = 0;
	// int * array = random_array (20);
	for (; i < NUM; ++ i) {
		printf ("arr [%d] = %d\n", i, a [i]);
	}
	printf ("\n--------------------\n");

	// insert_sort ((void*) a, NUM);
	insert_sort_t ((void*) a, NUM, sizeof (int), cmp_int_func);
	for (i = 0; i < NUM; ++ i) {
		printf ("arr [%d] = %d\n", i, a [i]);
	}
	// printf ("\n--------------------\n");
	return 0;
}



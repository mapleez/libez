#include <stdio.h>
// #include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

# define PTR_SWAP(A, B)   \
		do { \
			*(intptr_t*) (A) ^= *(intptr_t*) (B); \
			*(intptr_t*) (B) ^= *(intptr_t*) (A); \
			*(intptr_t*) (A) ^= *(intptr_t*) (B); \
		} while (0)

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

int binary_search (int* arr, int num, int key) {
	int mid, high = num - 1, low = 0;
	while (low <= high) {
		mid = (high + low) / 2;
		if (arr [mid] == key)
			return mid;
		else if (arr [mid] > key)
			high = mid - 1;
		else /*if (arr [mid] < key)*/
			low = mid + 1;
	}
	return -1;
}

int binary_search_t (void* arr, int num, size_t elm_size, cmp_func fxn, void* key) {
	int mid, high = num - 1, low = 0;
	while (low <= high) {
		mid = (high + low) / 2;
		if (0 == fxn (arr + mid * elm_size, key))
			return mid;
		else if (-1 == fxn (arr + mid * elm_size, key))
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
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
	else if (*(int*)a == *(int*) b) 
		return 0;
	else
		return 1;
}
#include <stdint.h>

// #	define tobigend16(___D)  (((uint16_t)((___D) & 0xff00) >> 8) | ((uint16_t)((___D) & 0x00ff) << 8))
// #	define tolittleend16(___D) tobigend16(___D)
// #	define tolittleend16(___D)  (((uint16_t)((___D) & 0xff00) >> 8) | ((uint16_t)((___D) & 0x00ff) << 8))

#	define BASIC_SWAP(___A, ___B) \
		do {  \
			(___A) ^= (___B);  \
			(___B) ^= (___A);  \
			(___A) ^= (___B);  \
		} while (0)

int main (int argc, char* argv []) {
	uint32_t x = 0x00323331;
	uint32_t x1 = 0x01020304;
	long long y = 0x01020304;
	uint32_t* px = &x;
	long long *py = &y;
	// intptr_t temp;

	printf ("%i, %i\n", px, py);
	// PTR_SWAP (px, py);
	// BASIC_SWAP (x, x1);

	((intptr_t*) px) ^= ((intptr_t*) py);
	((intptr_t*) py) ^= ((intptr_t*) px);
	((intptr_t*) px) ^= ((intptr_t*) py);

	printf ("%i, %i\n", px, py);
	return 0;
}

#if 0
int
main (int argc, char* argv []) {
#ifdef NUM
#undef NUM
#	define NUM 10
#endif
	int i = 0;
	int * array = random_array (NUM);
	for (; i < NUM; ++ i) {
		printf ("arr [%d] = %d\n", i, array [i]);
	}
	printf ("\n--------------------\n");

	// insert_sort ((void*) a, NUM);
	// insert_sort_t ((void*) a, NUM, sizeof (int), cmp_int_func);
	// selection_sort (array, 20);
	
	// if (array)
	// bubble_sort_t (array, 5, sizeof (int), cmp_int_func);
	bubble_sort (array, NUM);
//	else 
//		printf ("%s\n", "error...");
// 	sleep (2);
	for (i = 0; i < NUM; ++ i) {
		printf ("arr [%d] = %d\n", i, array [i]);
	}
	printf ("\n--------------------\n");
	for (i = NUM - 1; i >= 0; -- i) {
		printf ("search %d: %d\n", 
				array [i], 
				binary_search_t (array, NUM, sizeof (int), cmp_int_func, array + i));
	}

	printf ("\n--------------------\n");
	printf ("search %d: %d\n", 
			i, 
			binary_search_t (array, NUM, sizeof (int), cmp_int_func, &i));
	return 0;
}

#endif




#if 0

void _disp_each (const void* _elm) {
	int value = *(int*) _elm;
	printf ("%d ", value);
}

int main (int argc, 
		char* argv []) {

	display_array (random_int_array (20), 20, sizeof (int), _disp_each);
	// wchar_t* csd = L"中国";
	// wprintf ("%s\n", csd);
	// return 0;

}

#endif 


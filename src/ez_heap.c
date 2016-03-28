#include "ez_heap.h"
#include "ez.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int __def_heap_data_release (void*);
static int __def_heap_data_copy (void*, const void*);
static int __def_heap_data_match (const void*, const void*);

// static void* 
// __precolate_down_minheap (void**, int, _minheap_data_match, int);
static void* __percolate_down_minheap (pez_minheap, int);

static void _ez_heap_disp (pez_heap);
static pez_heap _ez_heap_create (int);
static void _ez_heap_dispose (pez_heap);

/*
 * Create a new (min)heap, specify the initial capacity.
 * Return new alloced ptr. or NULL if error.
 * I suggest you call minheap_set* () function to set the
 * 3 functions: copy (), match () and release ().
 */
static pez_heap _ez_heap_create (int _capacity) {
	pez_heap ptr = (pez_heap) malloc (SIZE_HEAP);
	if (! ptr) return NULL;

	/* we escape the first element as NULL,
		 that is to say, element can be indexed
		 within the range from 1 to N. */
	ptr -> _ptr = (void**) malloc (sizeof (void*) 
			* (_capacity + 1));
	if (! ptr -> _ptr) goto err;

	ptr -> _capa = _capacity;
	ptr -> _size = 0;
	ptr -> _release = __def_heap_data_release;
	ptr -> _copy = __def_heap_data_copy;
	ptr -> _match = __def_heap_data_match;
	return ptr;

err:
	free (ptr);
	return NULL;
}

/* Create (min)heap */
pez_minheap _ez_maxheap_create (int _capacity) {
	return (pez_minheap) _ez_heap_create (_capacity);
}

/* Create (max)heap */
pez_maxheap ez_minheap_create (int _capacity) {
	return (pez_maxheap) _ez_heap_create (_capacity);
}


/*
 * Create a (min)heap, The array must be heap order.
 * Return NULL if error.
*/
pez_minheap ez_minheap_createbyarray (int _capacity, void** _arr) {
	pez_minheap ptr;
	int num = 0;
	if (! _arr) return ez_minheap_create (_capacity);
	ptr = (pez_minheap) malloc (SIZE_MINHEAP);
	if (! ptr) return NULL;

	/* we escape the first element as NULL,
		 that is to say, element can be indexed
		 within the range from 1 to N. */
	num = sizeof (void*) * (_capacity + 1);
	ptr -> _ptr = (void**) malloc (num);
	if (! ptr -> _ptr) goto err;
	memcpy (ptr -> _ptr + 1, _arr, num);

	ptr -> _capa = _capacity;
	ptr -> _size = _capacity;
	ptr -> _release = __def_heap_data_release;
	ptr -> _copy = __def_heap_data_copy;
	ptr -> _match = __def_heap_data_match;
	return ptr;

err:
	// if (ptr -> _ptr) free (ptr -> _ptr);
	free (ptr);
	return NULL;
}

/*
 * Insert a new element into (min)heap.
 * On successful, return the added index(1 ~ N)
 * Otherwise return 0 (RTNVAL_FAIL) if failure.
*/
int ez_minheap_insert 
(pez_minheap _heap, const void* _dat) {
	if (_heap && ! ez_minheap_isfull (_heap)) {
		int i = 0;
		for (i = ++ _heap -> _size; 
					_heap -> _match (_heap -> _ptr [i >> 1], _dat) 
						== BIGGER;
					i >>= 1)
			_heap -> _ptr [i] = _heap -> _ptr [i >> 1];
		_heap -> _ptr [i] = (void*) _dat;
		return i;
	} else 
		return 0;
}

/* */
static void*
__percolate_down_minheap (pez_minheap _heap, int _idx) {
// (void** _ptr, int _len, _minheap_data_match _match, int _idx) {
	int parent = _idx;
	int child = parent << 1;
	void** ptr = _heap -> _ptr;
	void* temp = ptr [_idx];

	for (; child <= _heap -> _size; child <<= 1) {
		if (child < _heap -> _size && _heap -> _match (
					ptr [child], ptr [child + 1]) == BIGGER)
			child ++; /* To right child. */
		if (_heap -> _match (ptr [child], temp) == SMALLER)
			ptr [parent] = ptr [child];
		else
			break;
		parent = child;
	}
	return ptr [parent] = temp;
}

/*
 * Delete minimum element (that is root element ;) ) 
 * in special _heap.
 * Return RTNVAL_SUCC (1) if successful. 
 * Otherwise return 0 (RTNVAL_FAIL).
*/
int ez_minheap_delmin (pez_minheap _heap) {
	int i = 1;
  int child = i << 1;
	void* last = NULL;
	if (! _heap) return RTNVAL_FAIL;
	if (_heap && ez_minheap_isempty (_heap)) return RTNVAL_FAIL;

	/* Is it nessesary? Or we'd better 
		 overwrite ptr, and return it. */
	_heap -> _release (_heap -> _ptr [i]);
	last = _heap -> _ptr [_heap -> _size];
	/* Percolate down minheap. */
	for (; child <= _heap -> _size; child <<= 1) {

		/* we find smaller child. */
		if (child < _heap -> _size && _heap -> _match (
			_heap -> _ptr [child], _heap -> _ptr [child + 1]) ==
				BIGGER)
			child ++;

		if (_heap -> _match (_heap -> _ptr [child], last) == SMALLER)
			_heap -> _ptr [i] = _heap -> _ptr [child];
			// _heap -> _copy (_ptr [i], _ptr [child]);
		else break;
		i = child;
	}
	_heap -> _ptr [i] = last;
	_heap -> _size --;
	// _heap -> _copy (_ptr [i], last);
	return RTNVAL_SUCC;
}

/*
 * If failure, return NULL
 * Otherwise return an allocated (min)heap.
*/
pez_minheap ez_minheap_build 
(void** _arr, int _len, _minheap_data_match _cmp) {
	int parent = _len >> 1; /* the last parent node. */
	pez_minheap heap;
	if (! _arr || ! (heap = ez_minheap_createbyarray (_len, _arr)))
			return NULL;
	if (_cmp) ez_minheap_setmatch (heap, _cmp);
	for (; parent >= 1; -- parent)
		__percolate_down_minheap (heap, parent);
	return heap;
}

/*
 * Dispose special _heap. Release all the element
 * by calling _heap -> _release.
*/
static void _ez_heap_dispose (pez_heap _heap) {
	int i = 0;
	if (! _heap) return;
	for (i = 1; i <= _heap -> _size; i ++)
		_heap -> _release (_heap -> _ptr [i]);
	free (_heap);
}

void ez_maxheap_dispose (pez_maxheap _heap) {
	_ez_heap_dispose ((pez_heap) _heap);
}

void ez_minheap_dispose (pez_minheap _heap) {
	_ez_heap_dispose ((pez_heap) _heap);
}


/*
 * Display all the element, the internal array of
 * _heap.
*/
static void _ez_heap_disp (pez_heap _heap) {
	int i = 1;
	if (! _heap) return;
	printf ("(min)heap size = %d, capacity = %d\n", 
			_heap -> _size, _heap -> _capa);
	for (; i <= _heap -> _size; ++ i)
		printf ("%i ", (long long int) _heap -> _ptr [i]);
	println ("");
}

void ez_minheap_disp (pez_minheap _heap) {
	_ez_heap_disp ((pez_heap) _heap);
}

void ez_maxheap_disp (pez_maxheap _heap) {
	_ez_heap_disp ((pez_heap) _heap);
}


static int 
__def_heap_data_release (void* _dat) {
	free (_dat);
	return 1;
}


static int 
__def_heap_data_copy (void* _dst, const void* _src) {
	_dst = (void*) _src;
	return 1;
}

static int 
__def_heap_data_match (const void* _a, const void* _b) {
	return _a > _b ? BIGGER : 
		_a == _b ? EQUAL : SMALLER;
}


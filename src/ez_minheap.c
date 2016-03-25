#include "ez_minheap.h"
#include "ez.h"
#include <stdio.h>
#include <stdlib.h>

static int __def_minheap_data_release (void*);
static int __def_minheap_data_copy (void*, const void*);
static int __def_minheap_data_match (const void*, const void*);

/*
 * Create a new (min)heap, specify the initial capacity.
 * Return new alloced ptr. or NULL if error.
 * I suggest you call minheap_set* () function to set the
 * 3 functions: copy (), match () and release ().
 */
pez_minheap ez_minheap_create (int _capacity) {
	pez_minheap ptr = (pez_minheap) malloc (SIZE_MINHEAP);
	if (! ptr) return NULL;

	/* we escape the first element as NULL,
		 that is to say, element can be indexed
		 within the range from 1 to N. */
	ptr -> _ptr = (void**) malloc (sizeof (void*) 
			* (_capacity + 1));
	if (! ptr -> _ptr) goto err;

	ptr -> _capa = _capacity;
	ptr -> _size = 0;
	ptr -> _release = __def_minheap_data_release;
	ptr -> _copy = __def_minheap_data_copy;
	ptr -> _match = __def_minheap_data_match;
	return ptr;

err:
	free (ptr);
	return NULL;
}


/*
 * Insert a new element into heap.
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
 * Dispose special _heap. Release all the element
 * by calling _heap -> _release.
*/
void ez_minheap_dispose (pez_minheap _heap) {
	int i = 0;
	if (! _heap) return;
	for (i = 1; i <= _heap -> _size; i ++)
		_heap -> _release (_heap -> _ptr [i]);
	free (_heap);
}


/*
 * Display all the element, the internal array of
 * _heap.
*/
void ez_minheap_disp (pez_minheap _heap) {
	int i = 1;
	if (! _heap) return;
	printf ("(min)heap size = %d, capacity = %d\n", 
			_heap -> _size, _heap -> _capa);
	for (; i <= _heap -> _size; ++ i)
		printf ("%i ", (long long int) _heap -> _ptr [i]);
	println ("");
}


static int 
__def_minheap_data_release (void* _dat) {
	free (_dat);
	return 1;
}


static int 
__def_minheap_data_copy (void* _dst, const void* _src) {
	_dst = (void*) _src;
	return 1;
}

static int 
__def_minheap_data_match (const void* _a, const void* _b) {
	return _a > _b ? BIGGER : 
		_a == _b ? EQUAL : SMALLER;
}


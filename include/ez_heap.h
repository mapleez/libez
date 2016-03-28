#ifndef _EZ_MINHEAP_H_
#	define _EZ_MINHEAP_H_

typedef int (* _heap_data_release) (void*);
typedef _heap_data_release 
	_minheap_data_release, _maxheap_data_release;

typedef int (* _heap_data_match)
	(const void*, const void*);
typedef _heap_data_match 
	_minheap_data_match, _maxheap_data_match;

typedef int (* _heap_data_copy)
	(void*, const void*);
typedef _heap_data_copy 
	_minheap_data_copy, _maxheap_data_copy;

/* I must say the (min)heap and (max)heap
	 are defined similarly.
 */
typedef struct ez_heap {
	int _capa;
	int _size;
	void** _ptr;
	_heap_data_release _release;
	_heap_data_match _match;
	_heap_data_copy _copy;
} ez_heap, ez_minheap, ez_maxheap,
		*pez_heap, *pez_minheap, 
		*pez_maxheap;

#	define SIZE_MINHEAP (sizeof (ez_minheap))
#	define SIZE_MAXHEAP (sizeof (ez_maxheap))
#	define SIZE_HEAP (sizeof (ez_heap))

#	define ez_heap_setfunc(___HEAP, ___FUNC, ___FUNCNAME)  \
		do { \
			if ((___HEAP) && (___FUNC)) \
				(___HEAP) -> ___FUNCNAME = ___FUNC;  \
		} while (0)

/* Copy */
#	define ez_minheap_setcopy(___HEAP, ___FUNC)  \
		ez_heap_setfunc (___HEAP, ___FUNC, _copy)
#	define ez_maxheap_setcopy(___HEAP, ___FUNC)  \
		ez_heap_setfunc (___HEAP, ___FUNC, _copy)

/* Match */
#	define ez_minheap_setmatch(___HEAP, ___FUNC)  \
		ez_heap_setfunc (___HEAP, ___FUNC, _match)
#	define ez_maxheap_setmatch(___HEAP, ___FUNC)  \
		ez_heap_setfunc (___HEAP, ___FUNC, _match)

/* Release */
#	define ez_minheap_setrelease(___HEAP, ___FUNC)  \
		ez_heap_setfunc (___HEAP, ___FUNC, _release)
#	define ez_maxheap_setrelease(___HEAP, ___FUNC)  \
		ez_heap_setfunc (___HEAP, ___FUNC, _release)

/* IsFull */
#	define ez_heap_isfull(___HEAP)   \
		((___HEAP) -> _capa == (___HEAP) -> _size)
#	define ez_minheap_isfull(___HEAP)   \
		ez_heap_isfull (___HEAP)
#	define ez_maxheap_isfull(___HEAP)   \
		ez_heap_isfull (___HEAP)

/* isempty */
#	define ez_heap_isempty(___HEAP)   \
		(0 == (___HEAP) -> _size)
#	define ez_minheap_isempty(___HEAP)   \
		ez_heap_isempty (___HEAP)
#	define ez_maxheap_isempty(___HEAP)   \
		ez_heap_isempty (___HEAP)

/* (min)heap */
extern pez_minheap ez_minheap_create (int);
extern int ez_minheap_insert (pez_minheap, const void*);
extern void ez_minheap_dispose (pez_minheap);
extern int ez_minheap_delmin (pez_minheap);
extern pez_minheap ez_minheap_build (void**, int, _minheap_data_match);

/* (max)heap */
extern pez_maxheap ez_maxheap_create (int);
extern int ez_maxheap_insert (pez_maxheap, const void*);
extern void ez_maxheap_dispose (pez_maxheap);
extern int ez_maxheap_delmin (pez_maxheap);
extern pez_maxheap ez_maxheap_build (void**, int, _maxheap_data_match);

#if  1
/* Display all elements of heap. */
extern void ez_minheap_disp (pez_minheap);
extern void ez_maxheap_disp (pez_maxheap);

#endif // 1

#endif // ~ _EZ_MINHEAP_H_


#ifndef _EZ_MINHEAP_H_
#	define _EZ_MINHEAP_H_

typedef int (* _minheap_data_release) 
	(void*);

typedef int (* _minheap_data_match)
	(const void*, const void*);

typedef int (* _minheap_data_copy)
	(void*, const void*);

typedef struct ez_minheap {
	int _capa;
	int _size;
	void** _ptr;
	_minheap_data_release _release;
	_minheap_data_match _match;
	_minheap_data_copy _copy;
} ez_minheap,
		*pez_minheap;

#	define SIZE_MINHEAP (sizeof (ez_minheap))

#	define ez_minheap_setfunc(___HEAP, ___FUNC, ___FUNCNAME)  \
		do { \
			if ((___HEAP) && (___FUNC)) \
				(___HEAP) -> ___FUNCNAME = ___FUNC;  \
		} while (0)

#	define ez_minheap_setcopy(___HEAP, ___FUNC)  \
		ez_minheap_setfunc (___HEAP, ___FUNC, _copy)

#	define ez_minheap_setmatch(___HEAP, ___FUNC)  \
		ez_minheap_setfunc (___HEAP, ___FUNC, _match)

#	define ez_minheap_setrelease(___HEAP, ___FUNC)  \
		ez_minheap_setfunc (___HEAP, ___FUNC, _release)

#	define ez_minheap_isfull(___HEAP)   \
		((___HEAP) -> _capa == (___HEAP) -> _size)

#	define ez_minheap_isempty(___HEAP)   \
		(0 == (___HEAP) -> _size)

extern pez_minheap ez_minheap_create (int);
extern int ez_minheap_insert (pez_minheap, const void*);
extern void ez_minheap_dispose (pez_minheap);
extern int ez_minheap_delmin (pez_minheap);

#if  1
extern void ez_minheap_disp (pez_minheap);

#endif // 1

#endif // ~ _EZ_MINHEAP_H_


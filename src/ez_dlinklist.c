#include "ez_dlinklist.h"
#include <stdlib.h>

pez_dlist ez_dlist_create (void) {
	pez_dlist list = (pez_dlist) malloc (SIZE_EZ_DLIST);
	if (! list) return NULL;
	list -> _match = NULL;
	list -> _free = NULL;
	list -> _dup = NULL;
	list -> _count = 0;
	list -> _head = list -> _tail = NULL;
	return list;
}

#	define MASK (~0 - 1)
void ez_dlist_dispose (pez_dlist* _list) {
	pdlist_elm head, tail;
	free_func free_elm;
// #ifdef DBG
// 	int i = 0;
// #endif
	head = (*_list) -> _head;
	tail = (*_list) -> _tail;
	free_elm = (*_list) -> _free;
	if (! head) { // empty list.
		// (*_list) -> _count = 0;
		free (*_list);
		*_list = NULL;
		return;
	}

	while ((*_list) -> _count & MASK) {
		pdlist_elm h = head -> _next, 
							 t = tail -> _prev;
		if (free_elm) {
			free_elm (head -> _value);
			free_elm (tail -> _value);
			head -> _value = tail -> _value = NULL;
		}
		free (head);
		free (tail);
		head = h;
		tail = t;
		(*_list) -> _count -= 2;

// #ifdef DBG
// 		i += 2;
// 		printf ("now released %d elements.\n", i);
// #endif
	}
	
	if ((*_list) -> _count) {
		if (free_elm) {
			free_elm (head -> _value);
			head -> _value = NULL;
		}
		free (head);
		-- (*_list) -> _count;
// #ifdef DBG
// 		i += 1;
// 		printf ("now released %d elements.\n", i);
// #endif
	}
	head = tail = NULL;
	free (*_list);
	*_list = NULL;
}
#	undef MASK

pdlist_elm ez_dlist_gethead (pez_dlist _list) {
	// void* ptr = _list -> _head ? 
	// 	_list -> _head -> _value : NULL;
	return _list -> _head;
}

pdlist_elm ez_dlist_gettail (pez_dlist _list) {
	// void* ptr = _list -> _tail ? 
	// 	_list -> _tail -> _value : NULL;
	return _list -> _tail;
}

// int ez_dlist_duplicate (pez_dlist, const pez_dlist);

// the _value must not be NULL
pdlist_elm ez_dlist_pushhead (pez_dlist _list, void* const _val) {
	pdlist_elm elm = (pdlist_elm) malloc (SIZE_EZ_DLIST_ELM);
	if (! elm) return NULL;
	elm -> _value = _val;
	elm -> _prev = NULL;
	elm -> _next = _list -> _head;
	if (! _list -> _count) 
		_list -> _tail = elm;
	else
		_list -> _head -> _prev = elm; // fuck !!!
	_list -> _head = elm;
	++ (_list -> _count);
	return elm;
}

// the _value must not be NULL
pdlist_elm ez_dlist_pushtail (pez_dlist _list, void* const _val) {
	pdlist_elm elm = (pdlist_elm) malloc (SIZE_EZ_DLIST_ELM);
	if (! elm) return NULL;
	elm -> _value = _val;
	elm -> _next = NULL;
	elm -> _prev = _list -> _tail;
	if (! _list -> _count) 
		_list -> _head = elm;
	else
		_list -> _tail -> _next = elm; // fuck !!!
	_list -> _tail = elm;
	++ (_list -> _count);
	return elm;
}

void ez_dlist_pophead (pez_dlist _list) {
	pdlist_elm elm = _list -> _head;
	if (! elm) return;
	if (_list -> _free) {
		_list -> _free (elm -> _value);
		// tmp = elm -> _value;
	}
	elm = elm -> _next;
	free (_list -> _head);
	_list -> _head = elm;
	-- (_list -> _count);
	// return tmp;
}

void ez_dlist_poptail (pez_dlist _list) {
	pdlist_elm elm = _list -> _tail;
	if (! elm) return; // empty list.
	if (_list -> _free) {
		_list -> _free (elm -> _value);
		// tmp = elm -> _value;
	}
	elm = elm -> _prev;
	free (_list -> _tail);
	_list -> _tail = elm;
	-- (_list -> _count);
	// return tmp;
}

// the _value must not be null
// search from head to tail.
pdlist_elm ez_dlist_search (pez_dlist _list, void* const _val) {
	pdlist_elm elm;
	elm = _list -> _head;
	while (elm) {
		if (_list -> _match) {
			if (_list -> _match (elm -> _value, _val))
				return elm;// -> _value;
		} else 
			if (elm -> _value == _val) 
				return elm;// -> _value;
		elm = elm -> _next;
	}
	return NULL;
}

// index ranges from 0 to N
pdlist_elm ez_dlist_getbyidx (pez_dlist _list, int _idx) {
	pdlist_elm elm;
	elm = _list -> _head;
	if (_idx < 0) return NULL;
	while (_idx && elm) {
		elm = elm -> _next;
		-- _idx;
	}
	if (! _idx)
		return elm; // -> _value;
	return NULL;
}

void display_dlist_head (pez_dlist _list, disp_each _disp) {
	pdlist_elm head = _list -> _head;
	while (head) {
		_disp (head);
		head = head -> _next;
	}
	printf ("list has %d elements \n", 
				_list -> _count);
}

void display_dlist_tail (pez_dlist _list, disp_each _disp) {
	pdlist_elm tail = _list -> _tail;
	while (tail) {
		_disp (tail);
		tail = tail -> _prev;
	}
	printf ("list has %d elements \n", 
				_list -> _count);
}


pez_dlist ez_dlist_duplicate (const pez_dlist _src) {
	pez_dlist dst = ez_dlist_create ();
	pdlist_elm elm = _src -> _head;
	if (! dst) return NULL;
	set_dlist_match (dst, _src -> _match);
	set_dlist_free (dst, _src -> _free);
	set_dlist_dup (dst, _src -> _dup);
	while (elm) {
		void* ptr = NULL;
		if (dst -> _dup) {
			ptr = dst -> _dup (elm -> _value);
			if (! ptr) {
				ez_dlist_dispose (&dst);
				return NULL;
			}
		} else
			ptr = elm -> _value;
		// in this function dst update _count field.
		if (! ez_dlist_pushtail (dst, ptr)) {
			ez_dlist_dispose (&dst);
			return NULL;
		}
	}
	return dst;
}



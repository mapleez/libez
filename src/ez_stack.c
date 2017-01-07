/*
	author : ez
	date : 2015/5/19
	describe : stack declaration
*/

#include "ez_stack.h"
#include "ez.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void default_stack_clean_func (const void*); 

pez_stack ez_stack_create (int _maxsize) {
	pez_stack s = (pez_stack) malloc (EZ_STACK_SIZE);
	if (s) {
		if (_maxsize <= 0) _maxsize = DEF_STACK_CAPACITY;
		s -> array = (T*) malloc (ELEMENT_SIZE * _maxsize);
		if (s -> array == NULL) {
			free (s);
			return s = NULL;
		}
		s -> sp = STACK_EMPTY_MARK;
		s -> capacity = _maxsize;
	}
	return s;
}

void ez_stack_clear (pez_stack _s) {
	if (_s) {
		T ptr = ez_stack_topandpop (_s);
		clean_func cls = _s -> cls ? 
			_s -> cls : default_stack_clean_func;
		while (ptr) {
			cls (ptr);
			ptr = ez_stack_topandpop (_s);
		}
		_s -> sp = STACK_EMPTY_MARK;
	}
}

T ez_stack_top (pez_stack _s) {
	if (! ez_stack_empty (_s)) {
		return _s -> array [_s -> sp];
	}
	return NULL;
}

bool ez_stack_pop (pez_stack _s) {
	if (! ez_stack_empty (_s)) {
		_s -> sp --;
		return true;
	}
	return false;
}

T ez_stack_push (pez_stack _s, const T _e) {
	if (! ez_stack_full (_s) && _e) {
		_s -> array [++ _s -> sp] = _e;
		return _e;
	}
	return NULL;
}

T ez_stack_topandpop (pez_stack _s) {
	if (! ez_stack_empty (_s))
		return _s -> array [_s -> sp --];
	return NULL;
}

void ez_stack_dispose (pez_stack _s) {
	ez_clean_stack (_s);
	if (_s && _s -> array)
		free (_s -> array);
	free (_s);
}


void default_stack_clean_func (const void* _e) {
	(void) _e;
}

#ifdef __debug__

void show (pez_stack _s) {
	if (_s != NULL && _s -> sp != EMPTY_MARK) {
		int i = 0;
		for (; i < _s -> sp; i ++) {
			printf ("%d ", _s -> array [i]);
		}
	} else {
		println ("empty stack");
	}
}

#endif // ~ __debug__


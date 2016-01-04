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



bool ez_stack_empty (pez_stack _s) {
	return ((_s -> sp) == EMPTY_MARK);
}

bool ez_stack_full (pez_stack _s) {
	return ((_s -> sp + 1) == 
			(_s -> capacity));
}

pez_stack ez_stack_create (int _maxsize) {
	pez_stack s = (pez_stack) malloc (_stk_size);
	if (s != NULL) {
		s -> array = (_tp *) malloc (_tp_size * _maxsize);
		if (s -> array == NULL) {
			free (s);
			return NULL;
		}
		s -> sp = EMPTY_MARK;
		s -> capacity = _maxsize;
	}
	return s;
}

void ez_stack_clear (pez_stack _s) {
	if (_s != NULL) {
		memset (_s -> array, 0, _s -> capacity);
		_s -> sp = EMPTY_MARK;
	}
}

_tp ez_stack_top (pez_stack _s) {
	if (! ez_stack_empty (_s)) {
		return _s -> array [_s -> sp];
	}
	return 0;
}

bool ez_stack_pop (pez_stack _s) {
	if (! ez_stack_empty (_s)) {
		_s -> sp --;
		return true;
	}
	return false;
}

bool ez_stack_push (pez_stack _s, _tp _e) {
	if (! ez_stack_full (_s)) {
		_s -> array [++ _s -> sp] = _e;
		return true;
	}
	return false;
}

_tp ez_stack_topandpop (pez_stack _s) {
	if (! ez_stack_empty (_s)) {
		return _s -> array [_s -> sp --];
	}
	return 0;
}

void ez_stack_dispose (pez_stack _s) {
	if (_s != NULL) {
		free (_s -> array);
		free (_s);
		_s = NULL;
	}
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


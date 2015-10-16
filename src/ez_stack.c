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



bool empty_stk (_stack _s) {
	return ((_s -> sp) == EMPTY_MARK);
}

bool full_stk (_stack _s) {
	return ((_s -> sp + 1) == 
			(_s -> capacity));
}

_stack create_stack (int _maxsize) {
	_stack s = (_stack) malloc (_stk_size);
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

void clear_stack (_stack _s) {
	if (_s != NULL) {
		memset (_s -> array, 0, _s -> capacity);
		_s -> sp = EMPTY_MARK;
	}
}

_tp top (_stack _s) {
	if (! empty_stk (_s)) {
		return _s -> array [_s -> sp];
	}
	return 0;
}

bool pop (_stack _s) {
	if (! empty_stk (_s)) {
		_s -> sp --;
		return true;
	}
	return false;
}

bool push (_stack _s, _tp _e) {
	if (! full_stk (_s)) {
		_s -> array [++ _s -> sp] = _e;
		return true;
	}
	return false;
}

_tp topandpop (_stack _s) {
	if (! empty_stk (_s)) {
		return _s -> array [_s -> sp --];
	}
	return 0;
}

void dispose_stack (_stack _s) {
	if (_s != NULL) {
		free (_s -> array);
		free (_s);
		_s = NULL;
	}
}

#ifdef __debug__

void show (_stack _s) {
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


#include "ez_gstack.h"
#include <stdlib.h>

int _ez_gstack_default_resize (pez_gstack _gs) {
	int newsize = _gs -> _capa << 1;
	void** ptr = realloc (_gs -> _array, 
			sizeof (void*) * newsize);
	if (! ptr) return RTNVAL_FAIL;
	_gs -> _array = ptr;
	_gs -> _capa = newsize;
	return RTNVAL_SUCC;
}

pez_gstack ez_gstack_create (int _capa) {
	pez_gstack res;
 	res = (pez_gstack) malloc (SIZE_GSTACK);
	if (! res) return NULL;
	res -> _count = 0;
	res -> _capa = _capa;
	res -> _release = NULL;
	res -> _array = malloc (sizeof (void*) * _capa);
	if (! res -> _array) {
		free (res);
		return NULL;
	}
	return res;
}

void ez_gstack_release (pez_gstack _gs) {
	int i = _gs -> _count;
	if (_gs -> _array) {
		ez_gstack_clean (_gs);
		free (_gs -> _array);
	}
	free (_gs);
}


void* ez_gstack_push (pez_gstack _gs, void* _elm) {
	if (! _elm || ! _gs) return NULL;
	// if _count > _capa, it might be error!
	if (_gs -> _count >= _gs -> _capa &&
			_ez_gstack_default_resize (_gs) != RTNVAL_SUCC) 
		return NULL;
	return _gs -> _array [_gs -> _count ++] = _elm;
}

void* ez_gstack_top (pez_gstack _gs) {
	if (! _gs) return NULL;
	// first in last out
	if (_gs -> _count)
		return _gs -> _array [_gs -> _count - 1];
	return NULL;
}

void ez_gstack_pop (pez_gstack _gs) {
	void* elm = ez_gstack_top (_gs);
	if (elm) {
		if (_gs -> _release) _gs -> _release (elm);
		else free (elm);
		_gs -> _count --;
	}
}

int ez_gstack_clean (pez_gstack _gs) {
	if (_gs -> _array) {
		if (_gs -> _release)
			while (_gs -> _count) 
				_gs -> _release (_gs -> _array [-- _gs -> _count]);
		else 
			while (_gs -> _count) 
				free (_gs -> _array [-- _gs -> _count]);
	}
	return RTNVAL_SUCC;
}



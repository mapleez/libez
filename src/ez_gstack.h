#ifndef _EZ_GSTACK_H_
#	define _EZ_GSTACK_H_

#include "ez.h"

// release each element
typedef int (* _gstack_data_release) (void*);

// generic stack
typedef struct ez_gstack {
	int _capa;
	int _count;
	void** _array;
	_gstack_data_release _release;
} ez_gstack,
	* pez_gstack;

#	define SIZE_GSTACK (sizeof (ez_gstack))

extern pez_gstack ez_gstack_create (int _capa);
extern void ez_gstack_release (pez_gstack);
static inline int ez_gstack_getcount (pez_gstack _gs) {
	return _gs ? _gs -> _count : 
		RTNVAL_ERR;
}

static inline void ez_gstack_setrelease 
(pez_gstack _gs, _gstack_data_release _r) {
	_gs -> _release = _r;
}

extern void* ez_gstack_push (pez_gstack, void*);
extern void ez_gstack_pop (pez_gstack);
extern void* ez_gstack_top (pez_gstack);
extern int ez_gstack_clean (pez_gstack);

#endif // ~ _EZ_GSTACK_H_


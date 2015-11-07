#include <stdlib.h>
#include "ez.h"
#include "ez_thread.h"

static void ez_def_mutex_create (void** _mutex) {
	*_mutex = malloc (sizeof (int));
	*(int*) *_mutex = 0;
}

static void ez_def_mutex_destroy (void *_mutex) {
	free (_mutex);
	_mutex = NULL;
}

static void ez_def_mutex_lock 
	(volatile void* _param)
{
	volatile int* mutex = _param;
	do {
		// spin lock
		while (*mutex);
		(*mutex)++;
		if (*mutex == 1) break;
		(*mutex)--;

	} while (1);
}

static void ez_def_mutex_unlock 
	(volatile void* _mutex)
{
	(*(int*) _mutex)--;
}


/* net_set_mutex_funcs:
 *  Installs user-provided mutex create/destroy/lock/unlock 
 *  functions.  They may use the integer pointer parameter for 
 *  coordination such that a `lock' call only terminates if no 
 *  other thread is between calling `lock' and `unlock'.  
 *  `create' will be called once beforehand to create the mutex,
 *  and `destroy' will be called later on to destroy it.
 */
void ez_set_mutex_funcs (
	void (* _create)  (void **),
	void (* _destroy) (void *),
	void (* _lock)    (volatile void *),
	void (* _unlock)  (volatile void *)
)
{
	if (_create) {
		ez_mutex_create = _create;
		ez_mutex_destroy = _destroy;
		ez_mutex_lock = _lock;
		ez_mutex_unlock = _unlock;
	} else {
		ez_mutex_create = ez_def_mutex_create;
		ez_mutex_destroy = ez_def_mutex_destroy;
		ez_mutex_lock = ez_def_mutex_lock;
		ez_mutex_unlock = ez_def_mutex_unlock;
	}
}



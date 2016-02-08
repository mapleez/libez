#ifndef _EZ_SRV_H_
#	define _EZ_SRV_H_

#include "ez_log.h"
#include "ez_event.h"

#	define DEFAULT_CONN_SOCK 32

typedef struct ezsrv {
	int _sock;
	pez_logger _flog;
	pezevent_loop _loop;
	// int (* _init) (pezsrv, void*);
	// void (* _dispose) (pezsrv);
} ezsrv,
	 * pezsrv;

#	define SIZE_EZSRV (sizeof (struct ezsrv))

extern pezsrv ezsrv_create ();
#	define ezsrv_setinit(___S, ___F) (___S) -> _init = (___F)
#	define ezsrv_setdispose(___S, ___F) (___S) -> _dispose = (___F)

extern int ezsrv_init (pezsrv, void*);
extern void ezsrv_dispose (pezsrv);
extern void ezsrv_start (pezsrv);

#endif // ~ _EZ_SRV_H_

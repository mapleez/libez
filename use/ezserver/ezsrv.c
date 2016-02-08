#include "ezsrv.h"
#include <stdlib.h>

// console logger.
pez_logger _clog;
pezsrv _server;

// global function.
static void _initialize ();
static void _uninitialize ();

// register function of file log
static void _flog_init (pez_logger, void*);
static void _flog_release (pez_logger*);

// register function of server
// static int _srv_init (pezsrv, void*);
// static void _srv_dispose (pezsrv);

// ------------ global initialize -----------
static void _initialize () {
	_clog = ez_logger_new (NULL, NULL, LOGTYPE_CONSOLE, NULL);
	_server = ezsrv_create ();
	if (! _clog || ! _server) goto err;

	// ezsrv_setinit (_server, _srv_init);
	// ezsrv_setdispose (_server, _srv_dispose);
	return;

err:
	println ("Error in printing log string.");
	if (_clog) ez_logger_despose (&_clog);
	if (_server) ezsrv_dispose (_server);
	exit (-1);
}

// global dispose.
static void _uninitialize () {
	if (_clog) ez_logger_despose (&_clog);
	if (_server) ezsrv_dispose (_server);
}


// ----------- Implementation of Ezserver. ----------
pezsrv ezsrv_create () {
	pezsrv srv = (pezsrv) malloc (SIZE_EZSRV);
	if (! srv) return NULL;

	srv -> _flog = ez_logger_new (NULL, NULL, LOGTYPE_FILE, NULL);
	srv -> _loop = ezevent_create_eventloop (DEFAULT_CONN_SOCK);
	if (! srv -> _flog || ! srv -> _loop) goto err;
	// srv -> _init = NULL;
	// srv -> _dispose = NULL;
	return srv;

err:
	if (srv -> _flog) ez_logger_despose (&(srv -> _flog));
	if (srv -> _loop) ezevent_despose_eventloop (srv -> _loop);
	free (srv);
	return NULL;
}

void ezsrv_dispose (pezsrv _srv) {
	// if (_srv -> _dispose) {
	// 	_srv -> _dispose (_srv);
	// 	return;
	// }
	if (_srv -> _flog) ez_logger_despose (& (_srv -> _flog));
	if (_srv -> _loop) ezevent_despose_eventloop (_srv -> _loop);
	free (_srv);
}

int ezsrv_init (pezsrv _srv, void* _arg) {
	// if (_srv -> _init)
	// 	return _srv -> _init (_srv, _arg);
	return RTNVAL_FAIL;
}

void ezsrv_start (pezsrv _srv) {
	println ("start loop thread.");
	println ("start flog thread.");
}

// int _srv_init (pezsrv _srv, void* _arg) {
// 	(void) _arg;
// 	(void) _srv;
// 	return RTNVAL_SUCC;
// }
// 
// void _srv_dispose (pezsrv _srv) {
// 	(void) _srv;
// }

// --------------- Main --------------

int main (int argc, char* argv []) {
	printf ("initialize...");
	_initialize ();
	printf ("Done!\n");

	ezsrv_start (_server);

	printf ("dispose...");
	_uninitialize ();
	printf ("Done!\n");
	return 0;
}


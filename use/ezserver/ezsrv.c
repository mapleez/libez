#include "ezsrv.h"
#include "internet/ez_socktools.h"
// #include "ez_log.h"
// #include "ez_event.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <errno.h>

// #include <netinet/in.h>
// #include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

// console logger.
static pez_logger _clog;
static pezsrv _server;
static int run = 1;
static unsigned long long _stream = 0;

// global function.
static void _initialize ();
static void _uninitialize ();
static void _signal_inthandler (int);

// register function of file log
static void _flog_init (pez_logger, void*);
static void _flog_release (pez_logger*);

// loop file procedure.
static void _bind_sock_proc (pezevent_loop, int, int, void*);
static void _client_sock_read (pezevent_loop, int, int, void*);
static void _client_sock_write (pezevent_loop, int, int, void*);

// ------------ global initialize -----------
static void _initialize () {
	_clog = ez_logger_new (NULL, NULL, LOGTYPE_CONSOLE, NULL);
	_server = ezsrv_create ();
	if (! _clog || ! _server) goto err;
	if (signal (SIGINT, _signal_inthandler) == SIG_ERR) {
		ez_logger_error (_clog, "Error in register SIGINT.");
		goto err;
	}
	if (ezsrv_init (_server, NULL) == RTNVAL_FAIL) {
		ez_logger_error (_clog, "Error in initialize server.");
		goto err;
	}

	return;

err:
	println ("Error in initializing, will now shutdown...");
	// if (_clog) ez_logger_despose (&_clog);
	// if (_server) ezsrv_dispose (_server);
	_uninitialize ();
	exit (-1);
}

// global dispose.
static void _uninitialize () {
	if (_clog) ez_logger_despose (&_clog);
	if (_server) ezsrv_dispose (_server);
}

static void _bind_sock_proc 
(pezevent_loop _loop, int _fd, int _mask, void* _data) {
	int fd, res;
	unsigned int addr_int;
	socklen_t addr_len = 0; // client socket
	struct sockaddr_in client_addr;
	pezsrv psrv = (pezsrv) _data;
	// addr_len = sizeof (struct sockaddr);
	fd = accept (_fd, (struct sockaddr*) &client_addr, &addr_len);

	if (fd == -1 || ! addr_len) { // error.
		ez_logger_alert (psrv -> _flog, "Error in accept client sock");
		ez_logger_alert (_clog, "Error in accept client sock");
		return;
	}

	addr_int = client_addr.sin_addr.s_addr;
	ez_logger_info (_clog, "accept socket %d connected"
			" from address %d.%d.%d.%d:%d", 
			fd, addr_int & 0xff,
			(addr_int & 0xff00) >> 8,
			(addr_int & 0xff0000) >> 16,
			(addr_int & 0xff000000) >> 24,
			(client_addr.sin_port));
	// set socket options.
	res = ez_setsock_keepalive (fd, 1, 3);
	if (res != RTNVAL_SUCC)
		println ("error in set socket keepalive.");

	if (ezevent_add_fileevent (_loop, fd, 
			EE_READABLE, _client_sock_read, _data) == RTNVAL_FAIL)
	{
		ez_logger_alert (psrv -> _flog, "Error in adding fileevent.");
		ez_logger_alert (_clog, "Error in adding fileevent.");
	}
}

static void _client_sock_read 
(pezevent_loop _loop, int _fd, int _mask, void* _data) {
	char buff [256] = {0, };
	int read_len = 0;
	read_len = recv (_fd, buff, 256, 0);
	if (read_len > 0) {
		printf (".");
		// ezevent_add_fileevent 
		// 	(_loop, _fd, EE_WRITABLE, _client_sock_write, );

		// int i = 0;
		// _stream += read_len;
		// for (; i < read_len; ++ i) {
		// 	printf ("0x%02x ", buff [i]);
		// 	if (! (i & 0x07) && i)
		// 		println ("");
		// }
		// println ("");
	} else if (read_len == 0) {
		ez_logger_info (_clog, "client %d closed...", _fd);
		ezevent_rm_fileevent (_loop, _fd, EE_READABLE);
		close (_fd);
	} else /*if (read_len == -1)*/ {
		if (errno == EAGAIN) {
			ez_logger_info (_clog, "client %d closed...", _fd);
			ezevent_rm_fileevent (_loop, _fd, EE_READABLE);
			close (_fd);
		}
	}
}

static void _client_sock_write 
(pezevent_loop _loop, int _fd, int _mask, void* _data) {
}

static void _signal_inthandler (int _signo) {
	ez_logger_info (_clog, 
			"Trigger SIGINT, will now break event loop");
	ezsrv_stop (_server);
}

// ----------- Implementation of Ezserver. ----------
pezsrv ezsrv_create () {
	pezsrv srv = (pezsrv) malloc (SIZE_EZSRV);
	if (! srv) return NULL;

	// srv -> _flog = ez_logger_new (NULL, NULL, LOGTYPE_FILE, NULL);
	srv -> _loop = ezevent_create_eventloop (DEFAULT_CONN_SOCK);
	if (/*! srv -> _flog ||*/ ! srv -> _loop) goto err;
	return srv;

err:
	if (srv -> _flog) ez_logger_despose (&(srv -> _flog));
	if (srv -> _loop) ezevent_despose_eventloop (srv -> _loop);
	free (srv);
	return NULL;
}

void ezsrv_dispose (pezsrv _srv) {
	if (_srv -> _flog) ez_logger_despose (& (_srv -> _flog));
	if (_srv -> _loop) ezevent_despose_eventloop (_srv -> _loop);
	free (_srv);
}

int ezsrv_init (pezsrv _srv, void* _arg) {
	struct sockaddr_in* addr;
	int tmp;
	_srv -> _sock = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_srv -> _sock == -1)
		goto err;

	addr = (struct sockaddr_in*) (& _srv -> _addr);
	addr -> sin_family = AF_INET;
	addr -> sin_port = htons (BIND_PORT); // big-endian decimal 9999
	addr -> sin_addr.s_addr = inet_addr (BIND_ADDR);

	if (bind (_srv -> _sock, 
		(struct sockaddr*) addr, sizeof (*addr)) || 
			listen (_srv -> _sock, DEFAULT_CONN_SOCK))
		goto err; // error.

	tmp = ezevent_add_fileevent (_srv -> _loop, 
			_srv -> _sock, EE_READABLE, _bind_sock_proc, _srv);
	if (tmp == RTNVAL_FAIL && tmp == RTNVAL_ERR)
		goto err;

	return RTNVAL_SUCC;

err:
	ezsrv_dispose (_srv);
	return RTNVAL_FAIL;
}

void ezsrv_start (pezsrv _srv) {
	ezevent_start_loop (_srv -> _loop);
}

void ezsrv_stop (pezsrv _srv) {
	ezevent_stop_loop (_srv -> _loop);
	ezevent_rm_fileevent (_srv -> _loop, 
			_srv -> _sock, EE_READABLE);
	close (_srv -> _sock);
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
	printf ("Initialize...");
	_initialize ();
	printf ("Done!\n");

	ez_logger_info (_clog, "Starting server.");
	ezsrv_start (_server);
	ez_logger_info (_clog, "Shutdown server.");

	printf ("Dispose...");
	_uninitialize ();
	printf ("Done!\n");
	return 0;
}



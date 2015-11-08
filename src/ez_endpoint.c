#include "internet/ez_endpoint.h"
#include <stdlib.h>

#ifdef __MSC_VER

#include <winsock2.h>
#elif defined __GNUC__

#include <sys/socket.h>
#include <sys/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

static int _default_read_callback (void*, void*);
static int _default_write_callback (void*, void*);

static int 
_default_tcp_conn_callback (void*, void*);

static int
_default_udp_conn_callback (void*, void*);

static int
_default_icmp_conn_callback (void*, void*);


#	define _default_read_buff_len 256
#	define _default_write_buff_len 256

pez_endpoint 
ez_endpoint_init 
	(int _domain, int _type, int _proto, 
	 callback _read, callback _write,
	 callback _conn, int _rdbuff_len, 
	 int _wtbuff_len) 
{

	int sockfd = 0;
	pez_endpoint res = NULL;
	sockfd = socket (_domain, _type, _proto);
	if (-1 == sockfd) 
		return NULL;

	res = (pez_endpoint) 
		malloc (sizeof (ez_endpoint));
	if (res)
		return NULL;

	// link list
	res -> _next = NULL;

	// callback functions
	res -> _send_caller = _write ? _write : 
		_default_write_callback;
	res -> _recv_caller = _read ? _read :
		_default_read_callback;
	res -> _conn_caller = _conn ? _conn :
		_default_tcp_conn_callback;

	// buffers
	res -> _recv_buff = malloc (_rdbuff_len ? 
			_rdbuff_len : _default_read_buff_len);
	res -> _send_buff = malloc (_wtbuff_len ? 
			_wtbuff_len : _default_write_buff_len);

	if (! res -> _recv_buff || 
		! res -> _send_buff) {
		free (res -> _recv_buff);
		free (res -> _send_buff);
		free (res);
		return NULL;
	} 

	return res;
}


int ez_endpoint_despose (pez_endpoint _endpnt) {
	if (_endpnt) {

		if (-1 != _endpnt -> _sockfd) {
			shutdown (_endpnt -> _sockfd, 
					SHUT_RDWR);
			close (_endpnt -> _sockfd);
			_endpnt -> _sockfd = -1;
		}

		_endpnt -> _next = NULL;

		if (_endpnt -> _recv_buff)
			free (_endpnt -> _recv_buff);

		if (_endpnt -> _recv_buff)
			free (_endpnt -> _send_buff);

		free (_endpnt);

		_endpnt = NULL;
	}

	return 1;
}

static int
_default_read_callback (void* _endpnt, void* _arg) {
	return -1;
}

static int
_default_write_callback (void* _endpnt, void* _arg){
	return -1;
}

static int
_default_tcp_conn_callback (void* _endpnt, void* _arg) {
	return -1;
}


#ifdef __cplusplus
}
#endif // ~ __cplusplus

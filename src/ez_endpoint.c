// #include "internet/ez_endpoint.h"
#include "internet/ez_channel.h"
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

static int _default_read_callback (void*, int, void*);
static int _default_write_callback (void*, int, void*);

static int 
_default_tcp_conn_callback (void*, void*);

static int
_default_udp_conn_callback (void*, void*);

static int
_default_icmp_conn_callback (void*, void*);


// #	define _default_read_buff_len 256
// #	define _default_write_buff_len 256

/*
   create an endpoint.

   @1 -- socket domain.
   @2 -- socket type.
   @3 -- protocol.
   @4 -- read call back, if NULL, will be 
     setted by default function.
   @5 -- write call back, if NULL, will be 
	 setted by default function.
   @6 -- connection call back, if NULL, will
     be setted by default function.
   @7 -- read buffer length.
   @8 -- write buffer length.

   Return ez_endpoint ptr if successful,
   else return NULL;
*/
pez_endpoint 
ez_endpoint_init 
	(int _domain, int _type, int _proto, 
	 rwcallback _read, rwcallback _write,
	 conncallback _conn)
	 // , int _rdbuff_len, 
	 // int _wtbuff_len
{

	int sockfd = 0;
	pez_endpoint res = NULL;
	sockfd = socket (_domain, _type, _proto);
	if (-1 == sockfd) 
		return NULL;

	res = (pez_endpoint) 
		malloc (sizeof (ez_endpoint));
	if (! res)
		return NULL;

	res -> _sockfd = sockfd;

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
	// res -> _recv_buff = malloc (_rdbuff_len ? 
	// 		_rdbuff_len : _default_read_buff_len);
	// res -> _send_buff = malloc (_wtbuff_len ? 
	// 		_wtbuff_len : _default_write_buff_len);

	// if (! res -> _recv_buff || 
	// 	! res -> _send_buff) {
	// 	free (res -> _recv_buff);
	// 	free (res -> _send_buff);
	// 	free (res);
	// 	return NULL;
	// } 

	return res;
}

extern pez_endpoint
 ez_endpoint_set_sentbuff (pez_endpoint _end, void* _buf) {
	 if (! _end || ! _buf || _end -> _send_buff)
		 return NULL;
	 _end -> _send_buff = _buf;
	 return _end;
}

extern pez_endpoint
 ez_endpoint_set_recvbuff (pez_endpoint _end, void* _buf) {
	 if (! _end || ! _buf || _end -> _recv_buff) 
		 return NULL;
	 _end -> _recv_buff = _buf;
	 return _end;
}

extern void* 
 ez_endpoint_get_sentbuff (pez_endpoint _end) {
	 if (! _end)
		 return NULL;
	 return _end -> _send_buff;
}

extern void*
 ez_endpoint_get_recvbuff (pez_endpoint _end) {
	 if (! _end)
		 return NULL;
	 return _end -> _recv_buff;
 }


/*
   Dispose socket and its buffer blocks.
   This function will shutdown both buffer
   and close socket.

   @1 -- an entity to dispose.
   It will always return 1;
*/
int ez_endpoint_despose (pez_endpoint _endpnt) {
	if (_endpnt) {

		if (-1 != _endpnt -> _sockfd) {
			shutdown (_endpnt -> _sockfd, 
					SHUT_RDWR);
			close (_endpnt -> _sockfd);
			_endpnt -> _sockfd = -1;
		}

		_endpnt -> _next = NULL;
		// we do not free the buffer memory.
		_endpnt -> _recv_buff = NULL;
		_endpnt -> _send_buff = NULL;

		// if (_endpnt -> _recv_buff)
		// 	free (_endpnt -> _recv_buff);
		// if (_endpnt -> _recv_buff)
		// 	free (_endpnt -> _send_buff);

		free (_endpnt);
		_endpnt = NULL;
	}

	return 1;
}

/*
 * Return received bytes number
 * @1 -- endpoint entity.
 * @2 -- channel entity.
*/
static int
_default_read_callback (void* _endpnt, int _len, void* _arg) {
	pez_endpoint end = _endpnt;
	pez_channel chan = _arg;
	int res = 0;
	if (! end || ! chan || ! end -> _recv_buff)
		return 0;
	res = recv (end -> _sockfd,
			end -> _recv_buff, _len, 0);
	return res;
}

/*
 * Default write callback to be Registed into
 * endpoint if user support NULL write callback.
 * @1 -- endpoint entity.
 * @2 -- channel entity.
*/
static int
_default_write_callback (void* _endpnt, int _len, void* _arg) {
	pez_endpoint end = _endpnt;
	pez_channel chan = _arg;
	int res = 0;
	if (! end || ! chan || ! end -> _send_buff)
		return 0;
	res = send (end -> _sockfd, 
			end -> _send_buff, _len, 0);
	// res = send (end -> _sockfd, 
	// 		end -> _recv_buff, 0xff, 0);
	return res;
}


/*
 * Default connect callback in TCP protocol,
 * to be Registed into endpoint if user 
 * support NULL write callback.
 * @1 -- endpoint entity.
 * @2 -- channel entity.
*/
static int
_default_tcp_conn_callback (void* _endpnt, void* _arg) {
	pez_endpoint end = _endpnt;
	pez_channel chan = _arg;
	int res = 0;
	if (! end || ! chan)
		return 0;
	res = connect (end -> _sockfd, 
			(struct sockaddr*) &chan -> _remote, 
			sizeof (struct sockaddr));
	if (! res) return 1; // successful
	return 0;
}


#ifdef __cplusplus
}
#endif // ~ __cplusplus

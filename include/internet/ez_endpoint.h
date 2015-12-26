#ifndef _EZ_ENDPOINT_H_
#	define _EZ_ENDPOINT_H_

#include "ez.h"

#ifdef __cplusplus
extern "C" {
#endif 


typedef struct _ez_endpoint 
	ez_endpoint, *pez_endpoint;

typedef int (*callback) (void*, void*);

/*
   socket array list, head list
*/
struct _ez_endpoint {
	pez_endpoint _next;

#if defined __linux__ || defined __GNUC__ || defined __MINGW__
	int _sockfd;
#else
	SOCKET _sockfd;
#endif // __linux__ || __GNUC___
	callback _send_caller;
	callback _recv_caller;
	callback _conn_caller;

	void* _recv_buff;
	void* _send_buff;
}; 

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

   Return ez_endpoint ptr if successful,
   else return NULL;
*/
extern pez_endpoint 
 ez_endpoint_init (int, int, int, callback, callback, callback);

extern pez_endpoint
 ez_endpoint_set_sentbuff (pez_endpoint, void*);

extern pez_endpoint
 ez_endpoint_set_recvbuff (pez_endpoint, void*);

extern void* 
 ez_endpoint_get_sentbuff (pez_endpoint);

extern void*
 ez_endpoint_get_recvbuff (pez_endpoint);


/*
   Dispose socket and its buffer blocks.
   This function will shutdown both buffer
   and close socket.

   @1 -- an entity to dispose.
   It will always return 1;
*/
extern int
 ez_endpoint_despose (pez_endpoint);

#ifdef __cplusplus
}
#endif

/*
extern int
 ez_endpoint_open ();


extern int
 ez_endpoint_close ();


extern int 
 ez_endpoint_write ();


extern int
 ez_endpoint_read ();


extern int
 ez_endpoint_poll ();

*/

#endif // ~ _EZ_ENDPOINT_H_


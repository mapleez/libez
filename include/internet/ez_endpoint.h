#ifndef _EZ_ENDPOINT_H_
#	define _EZ_ENDPOINT_H_

#include "ez.h"

/*
   socket array list, head list
*/

typedef void (callback*) (void*);

typedef 
struct _ez_endpoint {
	pez_endpoint* _next;

#if defined __linux__ || defined __GNUC__ || defined __MINGW__
	int _sockfd;
#else
	SOCKET _sockfd;
#endif // __linux__ || __GNUC___
	callback _send_caller;
	callback _recv_caller;

	void* _recv_buff;
	void* _send_buff;

} ez_endpoint
	* pez_endpoint;

/*
   create an endpoint.

   @1 -- socket domain.
   @2 -- socket type.
   @3 -- protocol.
   @4 -- read call back, if NULL, will set
	 default function.
   @5 -- write call back, if NULL, will set
     default function.
   @6 -- read buffer length.
   @7 -- write buffer length.

   Return ez_endpoint ptr if successful,
   else return NULL;
*/
extern pez_endpoint 
 ez_endpoint_init (int, int, int, callback, callback, int, int);


/*
   Dispose socket and its buffer blocks.

   @1 -- an entity to dispose.
   It will always return 1;
*/
extern int
 ez_endpoint_despose (pez_endpoint);


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


#ifndef _EZ_CHANNEL_H_
#	define _EZ_CHANNEL_H_

#include "ez.h"
#include "ez_endpoint.h"

#ifndef __linux__
#include <winsock2.h>
#else

#include <arpa/inet.h>
#endif

/*
   Socket array bind to a same remote address
*/
typedef struct _ez_channel {

	/* The endpoint list registed in
	 * this channel
	 */
	pez_endpoint _next;

	/*
	 * The sockaddr this channel have
	 * been bound.
	*/
	struct sockaddr_in _remote;

	/*
	 * Element count in list _next,
	*/
	int _num;

} ez_channel,
	* pez_channel;

// --------- channel -------------

/* Initialize channel
 * @1 address to bind.
 * @2 port to bind (for tcp and udp).
 * Return : If successful, a new channel will
 *    be created and returned its ptr. Otherwise
 *    return NULL.
*/
extern pez_channel
 ez_init_channel
 (char*, const unsigned short);

// configure all the channel.
// extern void
//  ez_config_channel 
//  (pez_channel, pez_chnl_conf);


/* 
 * Open all endpoints in this channel
 * @1 The channel to be opened.
 * Return : if successful, it would return
 *    the number of endpoint been opened 
 *    successfully almost.
 */
extern int
 ez_open_channel (pez_channel);


/* 
 * Add endpoint to the channel head.
 * @1 The target channel.
 * @2 The endpoint to be added.
 * Return : If success then return 1, 
 *     otherwise return 0.
*/
extern int
 ez_add_endpoint (pez_channel, pez_endpoint);


/* 
 * We only remove the endpoint from internel list,
 * but we do not dispose it.
 * @1 The target channel.
 * @2 The endpoint to be removed. We only cheched
 * if the socket number is equied.
 * Return : If success then return 1, otherwise
 *      it return 0;
*/
extern int
 ez_remove_endpoint (pez_channel, pez_endpoint);


/*
 * Send datas from all endpoints
 * maybe @2 could be remove! Humm ...
 * All the endpoint Will call its write callback
 *       that you registed or the default.
 * Return : returns the count of successfully
 *       calling write callback. That is, if 
 *       2 endpoint successfully call its 
 *       write callback, the return value would
 *       be 2. And if no one is successful, return
 *       0.
*/
extern int
 ez_channel_send (pez_channel, int, void*);


/*
 * recv datas from all endpoints
 * maybe @2 could be remove! @_*
 * All the endpoint Will call its recv callback
 *       that you registed or the default.
 * Return : returns the count of successfully
 *       calling recv callback. That is, if 
 *       2 endpoint successfully call its 
 *       write callback, the return value would
 *       be 2. And if no one is successful, return
 *       0.
*/
extern int
 ez_channel_recv (pez_channel, int, void*);


/* 
 * Dispose all the endpoints.
 * This function will return the remined
 * endpoint number in the list. That is to
 * say. If all the endpoint dispose successful,
 * then it will return 0. otherwise non zero;
*/
extern int
 ez_dispose_all (pez_channel);

// poll all endpoints
// extern int
//  ez_channel_poll (pez_channel);


// ---------- endpoint ------------


#endif // ~ _EZ_CHANNEL_H_



#ifndef _EZ_CHANNEL_H_
#	define _EZ_CHANNEL_H_

#include "ez.h"


/*
   Socket array bind to a same remote address
*/
typedef struct _ez_channel {

	pez_endpoint * _next;
	struct sockaddr_in _remote;
	int _num;

} ez_channel,
	* pez_channel;

// --------- channel -------------

// initialize channel
extern pez_channel
 ez_init_channel
 (const char*, const unsigned short);

// open all 
extern void
 ez_config_channel 
 (pez_channel, pez_chnl_conf);


// open all endpoints in this channel
extern int
 ez_open_channel (pez_channel);


// add endpoint to the channel head.
extern int
 ez_add_endpoint (pez_channel, pez_endpoint);


extern int
 ez_remove_endpoint (pez_channel, pez_endpoint);


// send datas from all endpoints
extern int
 ez_channel_send (pez_channel);


// recv datas from all endpoints
extern int
 ez_channel_recv (pez_channel);


// poll all endpoints
extern int
 ez_channel_poll (pez_channel);


// ---------- endpoint ------------


#endif // ~ _EZ_CHANNEL_H_



#ifndef _EZ_CHANNEL_H_
#	define _EZ_CHANNEL_H_

#include "ez.h"

typedef struct _ez_endpoint {
	pez_endpoint* _next;

#if defined __linux__ || defined __GNUC__ || defined __MINGW__
	int _sockfd;
#else
	SOCKET _sockfd;
#endif // __linux__ || __GNUC___

	void (_recv_callback*) (void*);
	void (_send_callback*) (void*);

	void* _recvdata;
	void* _senddata;

} ez_endpoint
	* pez_endpoint;


typedef struct _ez_chnl_conf {

	int _sendtimeout;

} ez_chnl_conf,
	* pez_chnl_conf;


typedef struct _ez_channel {

	pez_endpoint * _next;
	struct sockaddr_in _remote;
	int _num;

} ez_channel,
	* pez_channel;


// --------- channel -------------

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
 ez_channel_send (pez_channel, void*, int);


// recv datas from all endpoints
extern int
 ez_channel_recv (pez_channel, void*, int*);


// poll all endpoints
extern int
 ez_channel_poll (pez_channel);


// ---------- endpoint ------------

// send data at this endpoint;
// extern int
//  ez_endpoint_send (pez_endpoint, void*, int);
// 
// 
// // recv data at this endpoint;
// extern int
//  ez_endpoint_recv (pez_endpoint, void*, int*);
// 
// 
// // poll data at this endpoint;
// extern int
//  ez_endpoint_poll (pez_endpoint);
// 
// 
// // close this sock at this endpoint;
// extern int
//  ez_close_endpoint (pez_endpoint);
// 
// 
// // dispose this endpoint.
// extern int
//  ez_dispose_endpoint (pez_endpoint);


#endif // ~ _EZ_CHANNEL_H_



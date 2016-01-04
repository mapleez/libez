#include "internet/ez_channel.h"
#include "internet/ez_socktools.h"
#include <stdlib.h>

#ifdef __MSC_VER
static int initilized = 0;
#endif // ~ __MSC_VER


/* Initialize channel
 * @1 address to bind.
 * @2 port to bind (for tcp and udp).
 * Return : If successful, a new channel will
 *    be created and returned its ptr. Otherwise
 *    return NULL.
 */
pez_channel ez_init_channel 
(char* _addr, const unsigned short _port) {
	pez_channel channel;

#ifdef __MSC_VER
	if (! initilized) {
		// WINDOWS socket 2 initialize
		// TODO
		initialized = 1;
	}

#endif // __MSC_VER

	channel = (pez_channel) 
		calloc (sizeof (ez_channel), 1);
	if (! channel) return NULL;

	channel -> _next = NULL;

	channel -> _remote.sin_family = AF_INET;
	channel -> _remote.sin_port = 
		tobigend16 (_port); 
	channel -> _remote.sin_addr.s_addr = 
		ez_stringaddr_to_int (_addr);

	return channel;
}

// void ez_config_channel 
// (pez_channel _chan, pez_chnl_conf _conf) {
// }


/* 
 * Open all endpoints in this channel
 * @1 The channel to be opened.
 * Return : if successful, it would return
 *    the number of endpoint been opened 
 *    successfully almost.
 */
int ez_open_channel (pez_channel _chan) {
	int num = 0;
	pez_endpoint ptr;

	if (! _chan)
		return -1;
	// num = _chan -> _num;
	ptr = _chan -> _next;


	while (ptr) {
		// if failure, return -1
		num += ptr -> 
			_conn_caller (ptr, _chan);
		
		ptr = ptr -> _next;
	}

	// return the number of 
	// successful connection 
	return num;
}


/* 
 * Add endpoint to the channel head.
 * @1 The target channel.
 * @2 The endpoint to be added.
 * Return : If success then return 1, 
 *     otherwise return 0.
*/
int ez_add_endpoint 
	(pez_channel _chan, pez_endpoint _endpnt) {

	if (! _chan || ! _endpnt) return 0;
	_endpnt -> _next = _chan -> _next;
	_chan -> _next = _endpnt;
	++ _chan -> _num;
	return 1;
}


/* 
 * We only remove the endpoint from internel list,
 * but we do not dispose it.
 * @1 The target channel.
 * @2 The endpoint to be removed. We only cheched
 * if the socket number is equied.
 * Return : If success then return 1, otherwise
 *      it return 0;
*/
int ez_remove_endpoint 
	(pez_channel _chan, pez_endpoint _endpnt) {

	if (_chan) return 0;
	pez_endpoint ptr = _chan -> _next;
	pez_endpoint preptr = ptr;
	if (! ptr && _endpnt) return 0;

	do {
		if (ptr -> _sockfd == 
			_endpnt -> _sockfd) {

			// remove ptr from its list. 
			preptr -> _next = ptr -> _next;
			-- (_chan -> _num);
			return 1;
		}

		preptr = ptr;
		ptr = ptr -> _next;

	} while (ptr);

	return 0;
	/*
	if (ptr && ptr -> _sockfd == 
		_endpnt -> _sockfd) {
		pez_endpoint tmp = ptr -> _next;
		ptr -> _next = ptr -> _next -> _next;

		if (tmp -> _recvdata)
			free (tmp -> _recvdata);
		if (tmp -> _senddata)
			free (tmp -> _senddata);
		close (tmp -> _sockfd);
		free (tmp);

	} else 
		return 0;

	while (ptr -> _next) {
		if (ptr -> _next -> _sockfd ==
			_endpnt -> _sockfd)
			break;
	}

	if (ptr -> _next && ptr -> _next -> _sockfd == 
		_endpnt -> _sockfd) {
		pez_endpoint tmp = ptr -> _next;
		ptr -> _next = ptr -> _next -> _next;

		if (tmp -> _recvdata)
			free (tmp -> _recvdata);
		if (tmp -> _senddata)
			free (tmp -> _senddata);
		close (tmp -> _sockfd);
		free (tmp);

		return 1;
	} else 
		return 0;
	*/
}


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
int ez_channel_send 
	(pez_channel _chan, int _len, void* _arg) {
	fd_set wfds;
	struct timeval tv;
	int num = 0;
	pez_endpoint ptr = _chan -> _next;

	tv.tv_sec = 0;
	tv.tv_usec = 0;

	while (ptr) {

		FD_ZERO (&wfds);
		FD_SET (ptr -> _sockfd, &wfds);

		if (!! select (ptr -> _sockfd + 1,
			NULL, &wfds, NULL, &tv)) 
			ptr -> _send_caller (ptr, _len, _chan) &&
				++ num; 

		ptr = ptr -> _next;
	}

	return num;
}


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
int 
ez_channel_recv (pez_channel _chan, int _len, void* _arg) {
	fd_set rfds;
	struct timeval tv;
	int num = 0;
	pez_endpoint ptr = _chan -> _next;

	tv.tv_sec = 0;
	tv.tv_usec = 0;
	while (ptr) {

		FD_ZERO (&rfds);
		FD_SET (ptr -> _sockfd, &rfds);

		if (!! select (ptr -> _sockfd + 1,
			&rfds, NULL, NULL, &tv)) {
			ptr -> _recv_caller (ptr, _len, _chan) &&
				(++ num);
		} 
		// else {
		// 	println ("select no!");
		// }
		ptr = ptr -> _next;
	}
	return num;
}


/* 
 * Dispose all the endpoints.
 * This function will return the remined
 * endpoint number in the list. That is to
 * say. If all the endpoint dispose successful,
 * then it will return 0. otherwise non zero;
*/
int
ez_dispose_all (pez_channel _chan) {
	if (! _chan) return 0;
	pez_endpoint ptr = _chan -> _next;
	pez_endpoint next;

	while (ptr) {
		next = ptr -> _next;
		_chan -> _num -= 
			ez_endpoint_despose (ptr);
		ptr = next;
	}

	return _chan -> _num;
}



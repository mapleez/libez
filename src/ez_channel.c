#include "internet/ez_channel.h"
#include "internet/ez_socktools.h"

static int initilized = 0;

pez_channel ez_init_channel 
(const char* _addr, const unsigned short _port) {
	pez_channel channel;
#ifdef __MSC_VER
	if (! initilized) {
		// WINDOWS socket 2 initialize
		// TODO
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

void ez_config_channel 
(pez_channel _chan, pez_chnl_conf _conf) {
	// TODO
}


int ez_open_channel (pez_channel _chan) {
	int num = 0;
	pez_endpoint ptr = _chan -> _next;

	while (ptr) {
		ptr -> _sockfd = socket (AF_INET, 
				SOCK_STREAM, IPPROTO_TCP);
		ptr = ptr -> _next;
		num ++;
	}

	return num;
}


int ez_add_endpoint 
	(pez_channel* _chan, pez_endpoint _endpnt) {

	if (! _chan) return 0;
	_endpnt -> _next = _chan;
	*_chan = _endpnt;
	return 1;
}

int ez_remove_endpoint 
	(pez_channel _chan, pez_endpoint _endpnt) {
	pez_endpoint ptr = _chan -> _next;

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
	
}


int ez_channel_send 
	(pez_channel _chan, void* _bufs, int _size) {
}


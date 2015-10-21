#include "ez_sock.h"
#include <stdlib.h>


#ifdef __cplusplus
extern "C" {
#endif 

pez_inet_sock
ez_create_inet_sock 
(const char* _ip, const int _port) {
	pez_inet_sock sock = 
		malloc (sizeof (ez_inet_sock));
	sock -> _port = _port;
	sock -> _ip._ip_i = inet_addr (_ip);
	return sock;
}

void
ez_dispose_inet_sock (pez_inet_sock _psock) {
	if (_psock) free (_psock);
	_psock = NULL;
}

#ifdef __cplusplus
}
#endif 

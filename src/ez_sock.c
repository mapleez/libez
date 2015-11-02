#include "ez_sock.h"
#include <stdlib.h>
#include <string.h>


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

// OK, just for may C study :(
// char* __libez_create (int, int);
// 
// char* __libez_create (int _a, int _b) {
// 	char* res = malloc (3);
// 	*res = (char)_a;
// 	*(res + 1) = (char) _b;
// 	*(res + 2) = '\0';
// 	return res;
// }

char*
ez_addr_to_string
(char* _str, struct sockaddr_in* _addr) {
	unsigned char* ptr;
	if (! _str || ! _addr)
		return NULL;
	_str = '\0';
	ptr = (unsigned char*) 
		& (_addr -> sin_addr.s_addr);
	if (INADDR_ANY != *ptr)
		sprintf (_str, "%d.%d.%d.%d", ptr [0], ptr [1], ptr [2], ptr [3]);
	sprintf (strchr (_str, '\0'), ":%d", ntohs (_addr -> sin_port));
    return _str;
}

// if format is like "......" or "*", 
// return INADDR_ANY
// else return 
int
ez_stringaddr_to_int (int* _iaddr, char* _addr) {
	if (! _addr || !_iaddr)
		return -1;
	if ('*' == *_addr)
		return *_iaddr = 0;
	char* ptr = _addr;
	unsigned char* iptr = (unsigned char*) _iaddr;
	while ('\0' != *ptr) {
		if (isdigit (*ptr)) {
			*iptr = *iptr * 10 + (*ptr - '0');
			ptr ++;
		} else if ('.' == *ptr) {
			iptr += 1;
			ptr += 1;
		} else
			return -1;
	}

	return *_iaddr;
}

char*
ez_int_to_stringaddr (char* _addr, int _iaddr) {
	if (! _addr)
		return NULL;
	unsigned char* iptr = (unsigned char*) &_iaddr;

	// TODO...
	return NULL;
}


#ifdef __cplusplus
}
#endif 

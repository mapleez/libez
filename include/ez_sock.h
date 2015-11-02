#ifndef _EZ_SOCK_H_
#	define _EZ_SOCK_H_

#include "ez.h"
#ifdef _MSC_VER

#include <winsock2.h>

#elif  defined __GNUC__

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#endif // ~ __GNUC__

#ifdef __cplusplus
extern "C" {
#endif 

/* Inet socket */
typedef struct _ez_inet_sock {
	struct sockaddr* _addr;
	int _port;
	union {
		char _ip_c [4];
		uint32_t _ip_i;
	} _ip;
	int _sockfd;
} ez_inet_sock,
	* pez_inet_sock;

extern pez_inet_sock
 ez_create_inet_sock (const char*, const int);

extern void
 ez_dispose_inet_sock (pez_inet_sock);

extern char* 
 ez_addr_to_string (char*, struct sockaddr_in*);

extern int
 ez_stringaddr_to_int (int*, char*);

extern char*
 ez_int_to_stringaddr (char*, int);

#ifdef __cplusplus
}
#endif

#endif // ~ _EZ_SOCK_H_

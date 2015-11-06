#ifndef _EZ_SOCK_H_
#	define _EZ_SOCK_H_

#include "ez.h"


/* Inet socket */
typedef struct _ez_inet_sock {
	int _sockfd;
	struct sockaddr* _addr;
	// int _port;
	// union {
	// 	char _ip_c [4];
	// 	uint32_t _ip_i;
	// } _ip;
} ez_inet_sock,
	* pez_inet_sock;

extern pez_inet_sock
 ez_create_inet_sock (const char*, const int);

extern void
 ez_dispose_inet_sock (pez_inet_sock);


#ifdef __cplusplus
}
#endif

#endif // ~ _EZ_SOCK_H_

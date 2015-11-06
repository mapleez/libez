#ifndef _EZ_SOCKTOOLS_H_
#	define _EZ_SOCKTOOLS_H_

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

extern char* 
 ez_addr_to_string (char*, struct sockaddr_in*);

extern int
 ez_stringaddr_to_int (char*);

extern char*
 ez_int_to_stringaddr (char*, int);

extern void 
 ez_sockfd_to_point 
#if defined __GNUC__ || defined __MINGW__
 (int, pez_endpoint);
#else
 (SOCKET, pez_endpoint);
#endif

#ifdef __cplusplus
}
#endif // ~ _cpp


#endif // ~ _EZ_SOCKTOOLS_H_

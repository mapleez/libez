#ifndef _EZ_SOCKTOOLS_H_
#	define _EZ_SOCKTOOLS_H_

#include "ez.h"

#ifdef _MSC_VER

#include <winsock2.h>

#elif  defined __GNUC__

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

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

extern struct hostent*
 ez_hostnameto_hostent (const char*);

extern struct in_addr*
 ez_hostnameto_sockaddr (const char*);

/*
 * Get the bounded address from a socket fd.
 * If successful ,return 0, otherwise return 
 * -1;
 * This function will call function 
 *     getsockname ();
 * If the @1 is NULL, return -1;
*/
extern int
 ez_sockfd_to_point 
#if defined __GNUC__ || defined __MINGW__
 (int, struct sockaddr*);
#else
 (SOCKET, struct sockaddr*);
#endif

#ifdef __cplusplus
}
#endif // ~ _cpp


#endif // ~ _EZ_SOCKTOOLS_H_

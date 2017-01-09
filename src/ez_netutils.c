#include "ez.h"
#include "ez_netutils.h"

#include <arpa/inet.h> /* in_addr_t */
#include <netdb.h> /* addrinfo */
#include <sys/socket.h>

/**
 * IPv4 name resolver using getaddrinfo().
 *
 * @param name The name, as in "www.target.com"...
 * @return IPv4 address found (in network order), or 0 if not found.
 * If error occurred, -1 will be returned.
 */
in_addr_t host_resolv (char* _name) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
  /* Hints getaddrinfo() to return only IPv4 compatible addresses. */
  struct addrinfo hints = { 
		.ai_family = AF_UNSPEC, 
		.ai_flags = AI_ALL | AI_V4MAPPED 
	}, *res, *res0 = NULL;
#pragma GCC diagnostic pop

  in_addr_t addr = 0;
  int err;

	if (! _name) return -1;

  if ((err = getaddrinfo (_name, NULL, &hints, &res0)) != 0) {
    if (res0) freeaddrinfo (res0);
		return -1;
  }

  /* scan all the list. */
  for (res = res0; res; res = res -> ai_next) {
    switch (res -> ai_family) {
    	case AF_INET:
    	  addr = ((struct sockaddr_in *) res -> ai_addr) 
					-> sin_addr.s_addr;
    	  goto end_loop;

    	case AF_INET6:
    	  if (!addr)
    	    addr = ((struct sockaddr_in6 *) res -> ai_addr) 
						-> sin6_addr.s6_addr32 [3];
    }
  }

end_loop:
  // Free the linked list.
  if (res0)
    freeaddrinfo (res0);

  return addr;
}


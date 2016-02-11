#include "ez.h"
#include "internet/ez_socktools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/types.h>

#	define SERVER_IP "127.0.0.1"
#	define SERVER_PORT 9999

bytes sendbuff = "fnafnaljvnaljflnajflnvklakljfnglbaf";

int main (int argc, char* argv []) {

	int sockfd, sendbuff_len;
	int sent_len = 0;
	struct sockaddr_in srv_addr;

	sockfd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sockfd == -1) {
		println ("Error in creating socket."
				"Will now shutdown...");
		return -1;
	}
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = tobigend16 (SERVER_PORT);
	srv_addr.sin_addr.s_addr = inet_addr (SERVER_IP);

	if (connect (sockfd, (struct sockaddr*) &srv_addr, 
				sizeof (srv_addr)))
	{
		println ("Error in connecting server,"
				"will now shutdown...");
		return -1;
	}

	sendbuff_len = strlen (sendbuff);

	while (1) {
		sent_len = send (sockfd, sendbuff, sendbuff_len, 0);
		if (sent_len == -1) {
			printf ("Send error! errno = %d\n", errno);
		} else {
			// nothing to do ...
			// printf ("Sent %d length bytes.\n", sent_len);
		}
	}

	return 0;
}


#include "internet/ez_channel.h"
#include "internet/ez_socktools.h"
#include <stdlib.h>
#include <stdio.h>
// #include "internet/ez_endpoint.h"

int main (int argc, char* argv []) {
#if 0
	{
		int res = 0;
		bytes arg = (bytes) malloc (256);
		pez_channel chan = ez_init_channel ("10.14.4.167", 21);
		pez_endpoint end = ez_endpoint_init (AF_INET, 
				SOCK_STREAM, IPPROTO_TCP, NULL, NULL,
				NULL);
		res = ez_add_endpoint (chan, end);

		res = ez_open_channel (chan);
		res = ez_channel_recv (chan, 256, arg);
		res = ez_remove_endpoint (chan, end);

		res = ez_dispose_all (chan);
		println ("ok");
	}
#endif

	{
		struct in_addr* addr = ez_hostnameto_sockaddr ("www.baidu.com");
		if (! addr) {
			println ("bad!");
			return 0;
		}
		println ("good!");
		printf ("IP address:%s\n", inet_ntoa (*(struct in_addr*) addr));
	}


	// char* ptr = ez_addr_to_string (,);
	// printf ("%s\n", ptr);
	// int ipaddr = 0;
	// int res = 0;
	// unsigned char* ptr = '\0';
	// res = ez_stringaddr_to_int (&ipaddr, "....");

	// if (ptr != '\0');
	return 0;
}

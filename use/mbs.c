#include "ez_modbus.h"
// #include <unistd.h>
#include "internet/ez_channel.h"
#include "internet/ez_endpoint.h"
// #include <sys/socket.h>
// #include <sys/type.h>
#include <stdlib.h>

int main (int argc, char* argv []) {
	
	{
		pez_channel chan = ez_init_channel ("10.14.4.167", 502);
		pez_endpoint endpoint = ez_endpoint_init (AF_INET, SOCK_STREAM, 
				IPPROTO_TCP, NULL, NULL, NULL);
		int sent_endpoint = 0, recv_endpoint = 0, sockfd = 0;
		pmbs_tcp_req_body_rd read_holdings = 
			ezmbs_tcp_create_read_holdings (1, 99, 10);
		pmbs_tcp_rsp_rd rcv_buff = malloc (40);

		if (! chan || ! endpoint || ! read_holdings) {
			println ("error! malloc ()");
			return 0;
		}

		if (ez_endpoint_set_sentbuff (endpoint, read_holdings) &&
		ez_endpoint_set_recvbuff (endpoint, rcv_buff))
			println ("good register send buff and receive buff!");

		if (! ez_add_endpoint (chan, endpoint)) {
			println ("error! add endpoint");
			return 0;
		}

	  if (! ez_open_channel (chan)) {
			println ("error ! open channel");
			return 0;
		}

		sent_endpoint = ez_channel_send (chan, sizeof (read_holdings), NULL);
		if (sent_endpoint > 0) {
			println ("good sending!");
		}

		// round-robin.
		while (! recv_endpoint) {
			recv_endpoint = ez_channel_recv (chan, 40, NULL);
			if (recv_endpoint > 0)
				println ("good receiving!");
		}

		if (! ez_dispose_all (chan))
			println ("dispose successful!");
	}
	return 0;
}

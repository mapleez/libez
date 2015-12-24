#include "ez_modbus.h"

int main (int argc, char* argv []) {

	pmbs_tcp_req_body_rd read_frame = ezmbs_tcp_create_read_holdings (123, 0x1000, 20);
	pmbs_tcp_req_body_rd read_input = ezmbs_tcp_create_read_input (100, 100, 20);

	ezmbs_free_frame (read_frame);
	ezmbs_free_frame (read_input);
	printf ("%s\n", EZ_MBS_VERSION);
	return 0;
}

#include "ez_modbus.h"

#	define DATA_LEN 8 
uint16_t values [] = {
	1, 2, 3, 4, 5, 6, 7, 8
};

int main (int argc, char* argv []) {

	pmbs_tcp_req_body_rd read_frame = ezmbs_tcp_create_read_holdings (123, 0x1000, 20);
	pmbs_tcp_req_body_rd read_input = ezmbs_tcp_create_read_input (100, 100, 20);
	pmbs_tcp_req_body_wr_s write_reg = ezmbs_tcp_create_write_single_reg (100, 20, 103);
	pmbs_tcp_req_body_wr_s write_coil = ezmbs_tcp_create_write_single_coil (100, 20, coil_val_on);

	pmbs_tcp_req_body_wr_m write_regs = ezmbs_tcp_create_write_multi_regs (100, 20, DATA_LEN, values);

	ezmbs_free_frame (read_frame);
	ezmbs_free_frame (read_input);
	ezmbs_free_frame (write_reg);
	ezmbs_free_frame (write_coil);
	ezmbs_free_frame (write_regs);

	printf ("%s\n", EZ_MBS_VERSION);
	return 0;
}

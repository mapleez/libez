#ifndef _EZ_MODBUS_H_
#	define _EZ_MODBUS_H_

#include "ez_proto.h"
#	define EZ_MBS_MAJOR_VER     1
#	define EZ_MBS_MINOR_VER     1 
#	define EZ_MBS_VERSION ("ezmbs-v" __xstr (EZ_MBS_MAJOR_VER) "." \
		__xstr (EZ_MBS_MINOR_VER))

// mbs function code
#	define mbs_func_read_coils		0x01
#	define mbs_func_read_disperse	0x02
#	define mbs_func_read_holdings	0x03
#	define mbs_func_read_input		0x04
#	define mbs_func_write_col		0x05
#	define mbs_func_write_holding	0x06
#	define mbs_func_write_cols		0x0f
#	define mbs_func_write_holdings  0x10

#if EZ_MBS_MAJOR_VER > 1
#	define mbs_func_read_file 		0x14
#	define mbs_func_write_file		0x15
#endif // ~ EZ_MBS_VERSION

// for singly writing, 
// notice: the value must be big-endian, so the 
// real value of coil_val_on is 0xff00, you should not convert to 
// big-endian.
#	define coil_val_off  0x0000
#	define coil_val_on   0xff00
// for multiply writing
#	define coils_val_off 0x1
#	define coils_val_on  0x0


/*
 * Create modbus request frame to
 * read coils.
 *
 * @1 transfer flags.
 * @2 start register
 * @3 the number of coil
 * return : request frame
*/
extern pmbs_tcp_req_body_rd
ezmbs_tcp_create_read_coils (int, int, int);


/*
 * Create modbus request frame to
 * read register (funccode_t = 0x04).
 *
 * @1 transfer flags.
 * @2 start register
 * @3 the number of register 
 * return : request frame
*/
extern pmbs_tcp_req_body_rd
ezmbs_tcp_create_read_input (int, int, int);

/*
 * Create modbus request frame to
 * read disperse (funccode_t = 0x02).
 *
 * @1 transfer flags.
 * @2 start register
 * @3 the number of register 
 * return : request frame
*/
extern pmbs_tcp_req_body_rd
ezmbs_tcp_create_read_disperse (int, int, int);

/*
 * Create modbus request frame to
 * read holding register (funccode_t = 0x03).
 *
 * @1 transfer flags.
 * @2 start register
 * @3 the number of register 
 * return : request frame
*/
extern pmbs_tcp_req_body_rd
ezmbs_tcp_create_read_holdings (int, int, int);

/*
 * Release the memory of frame.
 *
 * @1 the frame to release.
*/
extern void
ezmbs_free_frame (void*);


/*
 * Create modbus request frame to
 * write single coil.
 *
 * @1 transfer flags.
 * @2 start register
 * @3 value to write into.
 * return : request frame
*/
extern pmbs_tcp_req_body_wr_s
ezmbs_tcp_create_write_single_coil (int, int, int);


/*
 * Create modbus request frame to
 * write single registers.
 *
 * @1 transfer flags.
 * @2 start register
 * @3 value to write into.
 * return : request frame
*/
extern pmbs_tcp_req_body_wr_s
ezmbs_tcp_create_write_single_reg (int, int, int);

/*
 * Create modbus request frame to
 * Write multiple registers.
 *
 * @1 transfer flags.
 * @2 start register
 * @3 the number of register.
 * @4 the value list, each register has 2 bytes.
 * return : request frame
*/
extern pmbs_tcp_req_body_wr_m
ezmbs_tcp_create_write_multi_regs (int, int, int, uint16_t*);

/*
 * Create modbus request frame to
 * write multiple coils.
 *
 * @1 transfer flags.
 * @2 start register
 * @3 value to write into.
 * return : request frame
*/
extern pmbs_tcp_req_body_wr_m
ezmbs_tcp_create_write_multi_coils (int, int, int, uint8_t*);


// parse reading-registers , each one has 16 bits
extern int ezmbs_tcp_parse_read_multi_regs16 (pmbs_tcp_rsp_rd, int*, uint16_t*);
extern int ezmbs_tcp_parse_read_multi_regs32 (pmbs_tcp_rsp_rd, int*, uint32_t*);

// parse reading-coils, each one has ...
extern int ezmbs_tcp_parse_read_multi_coils (pmbs_tcp_rsp_rd, uint16_t*);
// extern int ezmbs_tcp_parse_read_multi_coils (mbs_tcp_rsp_rd, uint32_t*);

#endif // ~ _EZ_MODBUS_H_

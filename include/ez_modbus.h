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
#	define mbs_func_write_hlodings  0x10

#if EZ_MBS_MAIN_VERSION > 1
#	define mbs_func_read_file 		0x14
#	define mbs_func_write_file		0x15
#endif // ~ EZ_MBS_VERSION

typedef struct _mbs_tcp_rsp_datablock {
	int _start_addr;
	int _count;
	int _devid;
	int _elm_size;
	void* _datas;
} mbs_tcp_rsp_datablock,
	* pmbs_tcp_rsp_datablock;

// error
#	define FUNC_CODE int

/*
   @1 function code
   @2 transport flag
   @3 device id
   @4 start address
   @5 register count
   @6 register value if nessesary, or NULL
   @7 created frame length
return : 
   return the byte string;
*/
extern bytes 
 ez_create_mbs_tcp_request (
		 FUNC_CODE, int, int, 
		 int, int, uint16_t*, int*);


/*
 * Create modbus request frame to
 * read single register or coils.
 *
 * @1 transfer flags.
 * @2 start register
 * @3 the number of coil
 * return : request frame
*/
extern pmbs_tcp_req_body_rd
ezmbs_tcp_create_read_coils (int, int, int);

extern pmbs_tcp_req_body_rd
ezmbs_tcp_create_read_input (int, int, int);

extern pmbs_tcp_req_body_rd
ezmbs_tcp_create_read_disperse (int, int, int);

extern pmbs_tcp_req_body_rd
ezmbs_tcp_create_read_holdings (int, int, int);

extern void
ezmbs_free_frame (void*);


/*
 * Create modbus request frame to
 * write single registers or coils.
 *
 * @1 start register
 * @2 transfer flags.
 * @3 value to write into.
 * return : request frame
*/
extern pmbs_tcp_req_body_wr_s
ezmbs_tcp_create_write_single (int, int, int);


#if 0
/*
   @1 request frame header ptr
   @2 response frame ptr
   @3 parsed data structure ptr
return :
	return response data block, 
	and parsed register count if
	successful.
	else return NULL and 0;
*/
extern int
 ez_parse_mbs_tcp_response (
		 pmbs_tcp_req_head,
		 pmbs_tcp_rsp,
		 pmbs_tcp_rsp_datablock);

#endif

#endif // ~ _EZ_MODBUS_H_

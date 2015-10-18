#ifndef _EZ_MODBUS_H_
#	define _EZ_MODBUS_H_

#include "ez_proto.h"

typedef struct mbs_tcp_rsp_datablock {
};

/*
   @1 function code
   @2 transport flag
   @3 device id
   @4 start address
   @5 register count
*/
extern bytes 
 ez_create_mbs_tcp_request (
		 FUNC_CODE, int, int, int, int);

extern mbs_tcp_rsp_datablock 
 ez_parse_mbs_tcp_response ();


#endif // ~ _EZ_MODBUS_H_

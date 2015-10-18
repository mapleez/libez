#ifndef _EZ_MODBUS_H_
#	define _EZ_MODBUS_H_

#include "ez_proto.h"

typedef struct _mbs_tcp_rsp_datablock {
	int _start_addr;
	int _count;
	int _devid;
	int _elm_size;
	void* _datas;
} mbs_tcp_rsp_datablock,
	* pmbs_tcp_rsp_datablock;

/*
   @1 function code
   @2 transport flag
   @3 device id
   @4 start address
   @5 register count
return : 
   return the byte string;
*/
extern bytes 
 ez_create_mbs_tcp_request (
		 FUNC_CODE, int, int, int, int);

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


#endif // ~ _EZ_MODBUS_H_

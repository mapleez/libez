#include "ez_modbus.h"
#include <stdlib.h>
#include <string.h>

/*
   @1 function code
   @2 transport flag
   @3 device id
   @4 start address
   @5 register count
return : 
   return the byte string;
*/
bytes
ez_create_mbs_tcp_request (
	FUNC_CODE func_code,
	int trans,
	int devid,
	int start,
	int reg_cnt)
{
	pmbs_tcp_req_head frame = (pmbs_tcp_req_head)
		malloc (sizeof (mbs_tcp_req_head));
	frame -> _trans = 
		(uint16_t) (trans & 0x0000ffff);

	frame -> _len = 0x0600;  // Big endian

	frame -> _proto = 0x00;
	frame -> _devid = (uint16_t) (devid & 0xff);
	frame -> _func = func_code;

	frame -> _body._start_addr = 
		(uint16_t) (((start & 0xff00) >> 8) | 
			((start & 0x00ff) << 8));

	frame -> _body._reg_count = 
		(uint16_t) (((reg_cnt & 0xff00) >> 8) |
			((start & 0x00ff) << 8));

	return (bytes) frame;
}


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
int
ez_parse_mbs_tcp_response (
		 pmbs_tcp_req_head req,
		 pmbs_tcp_rsp rsp,
		 pmbs_tcp_rsp_datablock datas)
{
	intptr_t dptr = 0;
	if (! req || ! rsp)
		return 0;
	
	if (! datas) 
		datas = (pmbs_tcp_rsp_datablock) 
		malloc (sizeof (mbs_tcp_rsp_datablock));
	datas -> _start_addr = 
		req -> _body._start_addr;

	datas -> _count = 
		req -> _body._reg_count;

	datas -> _devid = rsp -> _devid;
	datas -> _elm_size = 
		rsp -> _data_len / req -> _body._reg_count;

	datas -> _datas = malloc (rsp -> _data_len);
	dptr = (intptr_t) (&rsp -> _first_data);

	if (! memcpy (datas -> _datas, 
			(void*) dptr, rsp -> _data_len)) {
		free (datas);
		datas = NULL;
		return 0;
	}

	return rsp -> _data_len;
}



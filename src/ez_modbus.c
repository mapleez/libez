#include "ez_modbus.h"
#include <stdlib.h>
#include <string.h>

// static bytes* _create_request_01;
// static bytes* _create_request_02;
// static bytes* _create_request_03;
// static bytes* _create_request_04;


/*
   @1 function code
   @2 transport flag
   @3 device id
   @4 start address
   @5 register count
return : 
   return the byte string;
*/
// typedef bytes (*_create_req_1_4)(
// 	FUNC_CODE, int, int, int, int, int*);

/*
   function array,
   code from 1 to 4
 */
// static 
// _create_req_1_4 _func_1_4 [] = {
// 	// func = 0x01
// 	_create_request_01,
// 
// 	// func = 0x02
// 	_create_request_02,
// 
// 	// func = 0x03
// 	_create_request_03,
// 	
// 	// func = 0x04
// 	_create_request_04
// };

static bytes 
_func_1_4 (
	FUNC_CODE func_code,
	int trans,
	int devid,
	int start,
	int reg_cnt,
	int* frm_len) 
{
	pmbs_tcp_req_head frame = (pmbs_tcp_req_head)
		malloc (*frm_len = 
				sizeof (mbs_tcp_req_head));
	frame -> _trans = 
		(uint16_t) (trans & 0x0000ffff);

	frame -> _len = 0x0600;  // Big endian

	frame -> _proto = 0x00;
	frame -> _devid = (uint16_t) (devid & 0xff);

	// code = 0x01 ~ 0x04
	frame -> _func = func_code;

	frame -> _body._start_addr = 
		tobigend16 (start)
		// (uint16_t) (((start & 0xff00) >> 8) | 
		// 	((start & 0x00ff) << 8));

	frame -> _body._reg_count = 
		tobigend16 (reg_cnt);
		// (uint16_t) (((reg_cnt & 0xff00) >> 8) |
		// 	((reg_cnt & 0x00ff) << 8));

	return (bytes) frame;
}


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
	int reg_cnt,
	int* frm_len)
{
	if (func_code <= 4)
		return _func_1_4 (func_code, trans, 
				devid, start, reg_cnt, frm_len);
	else if (func_code <= 6)
	else if (func_code <= 0x10) {
	} else 
		return NULL;
	// pmbs_tcp_req_head frame = (pmbs_tcp_req_head)
	// 	malloc (*frm_len = 
	// 			sizeof (mbs_tcp_req_head));
	// frame -> _trans = 
	// 	(uint16_t) (trans & 0x0000ffff);

	// frame -> _len = 0x0600;  // Big endian

	// frame -> _proto = 0x00;
	// frame -> _devid = (uint16_t) (devid & 0xff);
	// frame -> _func = func_code;

	// frame -> _body._start_addr = 
	// 	(uint16_t) (((start & 0xff00) >> 8) | 
	// 		((start & 0x00ff) << 8));

	// frame -> _body._reg_count = 
	// 	(uint16_t) (((reg_cnt & 0xff00) >> 8) |
	// 		((reg_cnt & 0x00ff) << 8));

	// return (bytes) frame;
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

#if 1

// unit testing
int main (int argc, char* argv []) {
	int len = 0;
	bytes frame = ez_create_mbs_tcp_request (3, 0x9983, 0x1, 0x6332, 0x9828, &len);
	int i  =0;
	return 0;
}

#endif // DEBUG

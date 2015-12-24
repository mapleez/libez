#include "ez_modbus.h"
#include <stdlib.h>
#include <string.h>

static pmbs_tcp_req_body_rd
_ezmbs_tcp_create_read (int, int, int, int);

static void ez_panic (const char*);

static void ez_panic (const char* _str) {
	printf ("%s\n", _str);
}


#if 0
static bytes _func_1_4 (
	FUNC_CODE,
	int,
	int,
	int,
	int,
	int*); 

static bytes _func_5_6 (
	FUNC_CODE,
	int,
	int,
	int,
	int,
	int*);

static bytes _func_15_16 (
	FUNC_CODE,
	int,
	int,
	int,
	int,
	uint16_t*,
	int*);

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
	// frame -> _func = func_code;

	frame -> _body._start_addr = 
		tobigend16 (start);
		// (uint16_t) (((start & 0xff00) >> 8) | 
		// 	((start & 0x00ff) << 8));

	frame -> _body._reg_count = 
		tobigend16 (reg_cnt);
		// (uint16_t) (((reg_cnt & 0xff00) >> 8) |
		// 	((reg_cnt & 0x00ff) << 8));

	return (bytes) frame;
}


static bytes 
_func_5_6 (
	FUNC_CODE func_code,
	int trans,
	int devid,
	int addr,
	int col_val,
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

	// code = 0x05, 0x06
	frame -> _func = func_code;

	frame -> _body._start_addr = 
		tobigend16 (addr);

	frame -> _body._reg_count = 
		tobigend16 (col_val);

	return (bytes) frame;
}


static bytes
_func_15_16 (
	FUNC_CODE func_code,
	int trans,
	int devid,
	int start,
	int reg_cnt,
	uint16_t* vals,
	int* frm_len) 
{

	int frame_len = sizeof (mbs_tcp_req_10_head) 
		+ (reg_cnt << 1);

	pmbs_tcp_req_10_head frame = 
		(pmbs_tcp_req_10_head) malloc (*frm_len = frame_len);

	frame -> _comm._trans = 
		(uint16_t) (trans & 0x0000ffff);

	frame -> _comm._len = 0x0600;  // Big endian

	frame -> _comm._proto = 0x00;
	frame -> _comm._devid = 
		(uint16_t) (devid & 0xff);

	frame -> _comm._func = func_code;

	frame -> _comm._body._start_addr = 
		tobigend16 (start);

	frame -> _comm._body._reg_count = 
		tobigend16 (reg_cnt);

	// reg_cnt * 2
	frame -> _bytes = reg_cnt << 1; 

	if (memcpy (&frame -> _first_val, vals,
			frame -> _bytes))
		return (bytes) frame;
	else {
		*frm_len = 0;
		free (frame);
		return 
			(bytes) (frame = NULL);
	}
}	

#endif 

void ezmbs_free_frame (void* _ptr) {
	free (_ptr);
}

/*
 * Create modbus request frame to
 * read coils.
 *
 * @1 transfer flags.
 * @2 start address of coil 
 * @3 the number of coil
 * return : request frame
*/
pmbs_tcp_req_body_rd
ezmbs_tcp_create_read_coils (int _trans, int _addr, int _count) {
	return _ezmbs_tcp_create_read (_trans, _addr, 
			_count, mbs_func_read_coils);
}

/*
 * Create modbus request frame to
 * read holding registers.
 *
 * @1 transfer flags.
 * @2 start address of holding register.
 * @3 the number of holding register.
 * return : request frame
*/
pmbs_tcp_req_body_rd
ezmbs_tcp_create_read_holdings (int _trans, int _addr, int _count) {
	return _ezmbs_tcp_create_read (_trans, _addr, 
			_count, mbs_func_read_holdings);
}

/*
 * Create modbus request frame to
 * read disperse.
 *
 * @1 transfer flags.
 * @2 start address of disperse inputing.
 * @3 the number of disperse inputing.
 * return : request frame
*/
pmbs_tcp_req_body_rd
ezmbs_tcp_create_read_disperse (int _trans, int _addr, int _count) {
	return _ezmbs_tcp_create_read (_trans, _addr, 
			_count, mbs_func_read_disperse);
}

/*
 * Create modbus request frame to
 * read input register.
 *
 * @1 transfer flags.
 * @2 start address of input register.
 * @3 the number of input register.
 * return : request frame
*/
pmbs_tcp_req_body_rd
ezmbs_tcp_create_read_input (int _trans, int _addr, int _count) {
	return _ezmbs_tcp_create_read (_trans, _addr, 
			_count, mbs_func_read_input);
}


/*
 * Create modbus request frame to
 * read single register or coils.
 *
 * @1 start register
 * @2 transfer flags.
 * return : request frame
*/
static pmbs_tcp_req_body_rd
_ezmbs_tcp_create_read (int _trans, int _addr, int _count, int _func) {

	pmbs_tcp_req_body_rd frame = (pmbs_tcp_req_body_rd) 
		malloc (sizeof (*frame));
	if (! frame)
		ez_panic ("malloc a mbstcp_read_single frame error.");
	frame -> _hdr._trans = (uint16_t) (_trans & 0x0000ffff);
	frame -> _hdr._len = 0x0600;  // Big endian
	frame -> _hdr._proto = 0x00;
	frame -> _hdr._devid = 0;
	frame -> _func = (funccode_t) _func;
	frame -> _start_addr = tobigend16 (_addr);
	frame -> _reg_count = tobigend16 (_count);
	return frame;

	// if (func_code <= 4)
	// 	return _func_1_4 (func_code, trans, 
	// 			devid, start, reg_cnt, frm_len);
	// else if (func_code <= 6) // include 5, 6
	// 	return _func_5_6 (func_code, trans,
	// 			devid, start, reg_cnt, frm_len);
	// else if (func_code <= 0x10)// include 16, 15
	// 	return _func_15_16 (func_code, trans,
	// 			devid, start, reg_cnt, 
	// 			vals, frm_len);
// #if EZ_MBS_MAIN_VERSION <= 1
// 	else 
// 		return NULL;
// #endif // ~ EZ_MBS_VERSION
}


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
	return 0;
}
#endif 

#endif // DEBUG


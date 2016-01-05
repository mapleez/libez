#include "ez_modbus.h"
#include <stdlib.h>
#include <string.h>

static pmbs_tcp_req_body_rd
_ezmbs_tcp_create_read (int, int, int, int);

static pmbs_tcp_req_body_wr_s
_ezmbs_tcp_create_write_single (int, int, int, int);

static void ez_panic (const char*);
static void* ezmbs_malloc (size_t);

static void ez_panic (const char* _str) {
	printf ("%s\n", _str);
}

static void* ezmbs_malloc (size_t _sz) {
	if (_sz & (sizeof (long) - 1))
		_sz += sizeof (long) - (_sz & (sizeof (long) - 1));
	return malloc (_sz);
}


#if 0

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


static pmbs_tcp_req_body_rd
_ezmbs_tcp_create_read (int _trans, int _addr, int _count, int _func) {
	pmbs_tcp_req_body_rd frame = (pmbs_tcp_req_body_rd) 
		ezmbs_malloc (sizeof (*frame));
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
}

static pmbs_tcp_req_body_wr_s _ezmbs_tcp_create_write_single 
(int _trans, int _addr, int _val, int _func) {
	return (pmbs_tcp_req_body_wr_s) 
		_ezmbs_tcp_create_read (_trans, _addr, _val, _func);
}

/*
 * Create modbus request frame to
 * write single coil.
 *
 * @1 transfer flags.
 * @2 start register
 * @3 value to write into.
 * return : request frame
*/
pmbs_tcp_req_body_wr_s
ezmbs_tcp_create_write_single_coil (int _trans, int _start, int _val) {
	// it's important to convert into big-endian.
	return _ezmbs_tcp_create_write_single (_trans, _start, 
			tobigend16 (_val), mbs_func_write_col);
}


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
ezmbs_tcp_create_write_single_reg (int _trans, int _start, int _val) {
	return _ezmbs_tcp_create_write_single (_trans, _start, _val,
			mbs_func_write_holding);
}

/*
 * Create modbus request frame to
 * write multiple registers.
 *
 * @1 transfer flags.
 * @2 start register
 * @3 the number of register.
 * @4 the value list, each register has 2 bytes.
 * return : request frame
*/
extern pmbs_tcp_req_body_wr_m ezmbs_tcp_create_write_multi_regs 
(int _trans, int _start, int _count, uint16_t* _vals) {
	int byte_len = _count << 1, i = 0;
	uint16_t* dataptr = NULL;
	pmbs_tcp_req_body_wr_m frame = (pmbs_tcp_req_body_wr_m)
		ezmbs_malloc (sizeof (mbs_tcp_req_body_wr_m) + byte_len);
	if (!frame) {
		ez_panic ("Error.");
		return NULL;
	}

	frame -> _hdr._trans = _trans;
	frame -> _hdr._proto = 0;
	frame -> _hdr._len = tobigend16 (7 + byte_len); // BE
	frame -> _hdr._devid = 0;
	frame -> _func = mbs_func_write_holdings;
	frame -> _start_addr = tobigend16 (_start); // BE
	frame -> _count = tobigend16 (_count); // BE
	frame -> _byte_len = byte_len;
	dataptr = (uint16_t*) (&frame -> _value);
	for (; i < _count; ++ i)
		dataptr [i] = tobigend16 (_vals [i]); // BE
	return frame;
}

// NOTE: hmm... it should be tested detailedly;
/*
 * Create modbus request frame to
 * Write multiple coils.
 *
 * @1 transfer flags.
 * @2 start coils.
 * @3 the number of coils.
 * @4 the value list, each coils has 1 bytes. 0x01 if ON, otherwise
 *     0x00 for OFF. We treat non-zero byte as ON and zero as OFF.
 * return : request frame
*/
pmbs_tcp_req_body_wr_m ezmbs_tcp_create_write_multi_coils 
(int _trans, int _start, int _count, uint8_t* _vals) {
	int byte_len = 0, tmp = 0, word = 0, mod = _count & 0x0F;
	uint16_t* dataptr = NULL;
	pmbs_tcp_req_body_wr_m frame = NULL;
	// tmp = _count / 8;
	word = (_count / 16) + (!! mod);
	byte_len = word << 1; // ! tmp ? 2 : tmp + (!! mod);

	frame = (pmbs_tcp_req_body_wr_m)
		ezmbs_malloc (sizeof (mbs_tcp_req_body_wr_m) + byte_len);
	if (!frame) {
		ez_panic ("Error.");
		return NULL;
	}

	frame -> _hdr._trans = _trans;
	frame -> _hdr._proto = 0;
	frame -> _hdr._len = tobigend16 (7 + byte_len);
	frame -> _hdr._devid = 0;
	frame -> _func = mbs_func_write_cols;
	frame -> _start_addr = tobigend16 (_start);
	frame -> _count = tobigend16 (_count);
	frame -> _byte_len = (uint8_t) _count;
	dataptr = (uint16_t*) (&frame -> _value);

	// tmp = 0; // as dataptr offset.
	do {
		int ptr = 0, i = tmp << 4, ptr_len;
		ptr_len = word - tmp == 1 ? mod : 16;
		for (; ptr < ptr_len; ++ ptr)
			dataptr [tmp] |= (!! _vals [i + ptr]) << ptr;
		dataptr [tmp] = tobigend16 (dataptr [tmp]);
	} while (word > ++ tmp);

	return frame;
}


// return -1 if it's error frame, return 0 if parameter is NULL ptr,
int ezmbs_tcp_parse_read_multi_regs16 
(pmbs_tcp_rsp_rd _frm, int* _trans, uint16_t* _datas) {
	uint16_t * ptr;
	int afterwords = 0;
	if (! _frm || ! _trans || ! _datas) return 0;
	*_trans = tolocalend16 (_frm -> _hdr._trans);
	afterwords = tolocalend16 (_frm -> _hdr._len);
	if (afterwords > 3) {
		int i = 0;
		afterwords = tolocalend16 (_frm -> _data_len);
		ptr = (uint16_t*) _frm -> _first_data;
		for (; i < afterwords; ++ i)
			_datas [i] = tolocalend16 (ptr [i]);
		return (i + 1);
	} else // error frame.
		return -1;
}

int ezmbs_tcp_parse_read_multi_regs32 
(pmbs_tcp_rsp_rd _frm, int* _trans, uint32_t* _datas) {}


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

#endif // DEBUG


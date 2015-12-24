#ifndef _EZ_PROTO_H_

#	define _EZ_PROTO_H_

#include "ez.h"
#include <stdint.h>
#include <stdbool.h>

// for request frame header, and also the response
// frame header.
struct _mbs_tcp_req_head;

// for request frame
struct _mbs_tcp_req_body_wr_s;
struct _mbs_tcp_req_body_wr_m;
struct _mbs_tcp_req_body_rd;

// for response frame
struct _mbs_tcp_rsp_wr;
struct _mbs_tcp_rsp_rd;

#pragma pack (1)
typedef uint8_t funccode_t;

// for write function code
typedef
 struct _mbs_tcp_req_body_wr_s {
	/* header of request frame */
	mbs_tcp_req_head _hdr;

	/* function code */
	funccode_t _func;

	/* requesting start register address, BE */
	uint16_t _start_addr;

	/* value to write into */
	uint16_t _value;

} mbs_tcp_req_body_wr_s,
	*pmbs_tcp_req_body_wr_s;

// for write multiple unit function code
typedef
 struct _mbs_tcp_req_body_wr_m {
	/* header of request frame */
	mbs_tcp_req_head _hdr;

	/* function code */
	funccode_t _func;

	/* requesting start register address, BE */
	uint16_t _start_addr;

	/* value length */
	uint8_t _byte_len;

	/* 
	 * values to write into.
	 * If it's coil, each unit has 1 byte,
	 * otherwise each register has 2 bytes.
	*/
	uint8_t _value [];

} mbs_tcp_req_body_wr_m,
	*pmbs_tcp_req_body_wr_m;

// for read function code
typedef
 struct _mbs_tcp_req_body_rd {
	/* header of request frame */
	mbs_tcp_req_head _hdr;

	/* function code */
	funccode_t _func;

	uint16_t _start_addr;

	/* requesting register count, BE */
	uint16_t _reg_count;

} mbs_tcp_req_body_rd,
	*pmbs_tcp_req_body_rd;


// request frame header
typedef 
 struct _mds_tcp_req_head {

	/* transport flag, LE */
	uint16_t _trans;
	
	/* protocol flag, always be 0 */
	uint16_t _proto;

	/* the length of frame afterwords, BE */
	uint16_t _len;

	/* the modbus network device id */
	uint8_t  _devid;

} mbs_tcp_req_head,
	* pmbs_tcp_req_head;

// response frame header.
typedef mbs_tcp_req_head 
 mbs_tcp_rsp_head, *pmbs_tcp_rsp_head;

// response frame for read function code
typedef
 struct _mbs_tcp_rsp_rd {

	 mbs_tcp_rsp_head _hdr;
	
	/* function code */
	funccode_t _func;

	/* data length */
	uint8_t _data_len;

	/* 
	   the first byte, we
	   use this field to 
	   get first data address,
	   data unit is always 
	   Big endian (16 bits per
	   unit).
	*/
	uint8_t _first_data [];

} mbs_tcp_rsp_rd,
	* pmbs_tcp_rsp_rd;

// response frame for write function code
typedef
 struct _mbs_tcp_rsp_wr {

	 mbs_tcp_rsp_head _hdr;
	
	/* function code */
	funccode_t _func;

	/* start register address */
	uint16_t _start_addr;

	union {
		// the value after write.
		uint16_t _value;
		// the changed number of register.
		uint16_t _count;
	} _res;

} mbs_tcp_rsp_rd,
	* pmbs_tcp_rsp_rd;
#pragma pack ()

#endif // ~ _EZ_PROTO_H_


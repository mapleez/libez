#ifndef _EZ_PROTO_H_

#	define _EZ_PROTO_H_

#include "ez.h"
#include <stdint.h>
#include <stdbool.h>

#	define tobigend16(___D)  (((uint16_t)((___D) & 0xff00) >> 8) | ((uint16_t)((___D) & 0x00ff) << 8))
#	define tolittleend16(___D) tobigend16(___D)

struct _mbs_unit_be;
struct _mbs_unit_le;
struct _mbs_tcp_req_head;
struct _mbs_tcp_req_body;
struct _mbs_tcp_rsp;

#pragma pack (1)

/* big endian 16 bits unit */
typedef 
 struct _mbs_unit_be {
	uint8_t _hi;
	uint8_t _lo;
} mbs_unit_be,
	* pmbs_unit_be;

/* little endian 16 bits unit */
typedef 
 struct _mbs_unit_le {
	uint8_t _lo;
	uint8_t _hi;
} mbs_unit_le,
	* pmbs_unit_le;

typedef
 struct _mbs_tcp_req_body {
	/* requesting start register address, BE */
	uint16_t _start_addr;

	/* requesting register count, BE */
	uint16_t _reg_count;
} mbs_tcp_req_body;

// typedef mbs_unit mbs_count;
// typedef pmbs_unit pmbs_count;
#	define FUNC_CODE uint8_t

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

	/* function code */
	FUNC_CODE _func;

	/* request body */
	mbs_tcp_req_body _body;

} mbs_tcp_req_head,
	* pmbs_tcp_req_head;

typedef
struct _mbs_tcp_req_0f_head {
	/* the same as the one above */
	mbs_tcp_req_head _comm;

	/* byte length */
	uint8_t _bytes;

	/* output values */
	uint16_t _vals;
} mbs_tcp_req_0f_head,
	* pmbs_tcp_req_0f_head;

typedef
struct _mbs_tcp_req_10_head {
	/* the same as the one above */
	mbs_tcp_req_head _comm;

	/* byte length */
	uint8_t _bytes;

	/* register values */
	uint16_t _first_val;
} mbs_tcp_req_10_head,
	* pmbs_tcp_req_10_head;

typedef
 struct _mbs_tcp_rsp {
	
	/* transport flag, LE */
	uint16_t _trans;
	
	/* protocol flag, always be 0 */
	uint16_t _proto;

	/* the length of frame afterwords, BE */
	uint16_t _len;

	/* the modbus network device id */
	uint8_t  _devid;

	/* function code */
	FUNC_CODE _func;

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
	uint8_t _first_data;

} mbs_tcp_rsp,
	* pmbs_tcp_rsp;

#pragma pack ()



#endif // ~ _EZ_PROTO_H_
